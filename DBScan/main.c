#include <SDL.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h> 

#include "gui.h"
#include "point.h"
#include "dbscan.h"
#include "gaussian_distribution.h"

int main()
{
    // Init SDL
    ////////////////////////////////////////////////////////////

    // Define Window Width & Height
    const int WINDOW_WIDTH  = 600;
    const int WINDOW_HEIGHT = 600;

    // Create window and renderer
    SDL_Window* window     = create_window(WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_Renderer* renderer = create_renderer(&window);

    // Enable alpha blending
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    // Set window color to black
    clear_window(&renderer);
  
    ////////////////////////////////////////////////////////////
    // Generate k gaussian clusters dataset
    ////////////////////////////////////////////////////////////

    // Init random number generator
    srand(time(NULL));

    const int N = 5000;
    Point dataset[N];
    
    const int k = 5;
    GaussianDistribution gaussian_distributions[k];

    for(int i = 0; i < k; i++)
    {
        gaussian_distributions[i].mu_x    = ((double)rand())/RAND_MAX * WINDOW_WIDTH*0.8 + WINDOW_WIDTH*0.1;
        gaussian_distributions[i].mu_y    = ((double)rand())/RAND_MAX * WINDOW_HEIGHT*0.8 + WINDOW_HEIGHT*0.1;
        gaussian_distributions[i].sigma_x = ((double)rand())/RAND_MAX * 40 + 10;
        gaussian_distributions[i].sigma_y = ((double)rand())/RAND_MAX * 40 + 10;
    }
    
    generate_gaussian_clusters_dataset(dataset, N, gaussian_distributions, k);
   
    draw_classified_dataset(dataset, N, &renderer);
    SDL_RenderPresent(renderer);

    ///////////////////////////////////////////////////////////////
    // Density Based Spatial Clustering of applications with Noise
    // (DBSCAN) Algorithm
    ///////////////////////////////////////////////////////////////

    // Algorithm hyper-parameters
    double eps = 5;
    double minPts = 10;

    int cluster_counter = 0;

    for(int i = 0; i < N; i++)
    {
        
        // Check if point was already processed
        // in the inner loop
        if(dataset[i].label != -1)
        {
            continue;
        }   

        Vector* neighbors = find_neighbors(dataset,N, dataset[i], eps, BRUTE);
        
        if( neighbors->size < minPts )
        {
            dataset[i].label = -2;
            free(neighbors->array);
            free(neighbors);
            continue;
        }
        
        cluster_counter++;

        // Assign to point the current cluster number
        dataset[i].label = cluster_counter;


        for(int j = 0; j < neighbors->size; j++)
        {
            if( neighbors->array[j]->x == dataset[i].x & neighbors->array[j]->y == dataset[i].y)
            {
                continue;
            }

            if(j%10==0)
            {
                clear_window(&renderer);
                draw_classified_dataset(dataset, N, &renderer);
                SDL_RenderPresent(renderer);
            }
            

            if(neighbors->array[j]->label == -2)
            {
                neighbors->array[j]->label = cluster_counter;
            }

            if(neighbors->array[j]->label != -1)
            {
                continue;
            }

            neighbors->array[j]->label = cluster_counter;

            Vector * n2 = find_neighbors(dataset, N, *neighbors->array[j], eps, BRUTE);

            for(int k = 0; k < n2->size; k++)
            {
                vector_push_back(neighbors, n2->array[k]);
            }

            free(n2->array);
            free(n2);    
        }
        
        // free dynamic neighbors array
        free(neighbors->array);
        free(neighbors);
        
    }

    printf("Found %d clusters\n",cluster_counter);

    clear_window(&renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // RGBA
    SDL_RenderClear(renderer);
    draw_classified_dataset(dataset, N, &renderer);
    SDL_RenderPresent(renderer);
    
     // SDL Visualization Loop
    SDL_Event e;
    bool quit = false;
    while (!quit) 
    {

        while (SDL_PollEvent(&e) != 0)
        {
            
            if (e.type == SDL_QUIT) 
            {
                quit = 1;
            }
        }
    }


    return 0;
}