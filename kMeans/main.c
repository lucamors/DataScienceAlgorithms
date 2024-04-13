// k-Means implementation
#include <SDL.h>
#include <time.h>

#include <stdio.h>
#include <stdbool.h>

#include "gui.h"
#include "kmeans.h"

int main(int argc, char* argv[]) 
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

    const int N = 50000;
    Point dataset[N];

    GaussianDistribution g1 = {
        .mu_x    = ((double)rand())/RAND_MAX * WINDOW_WIDTH*0.8 + WINDOW_WIDTH*0.1,
        .mu_y    = ((double)rand())/RAND_MAX * WINDOW_HEIGHT*0.8 + WINDOW_HEIGHT*0.1,
        .sigma_x = ((double)rand())/RAND_MAX * 40 + 10,
        .sigma_y = ((double)rand())/RAND_MAX * 40 + 10,
    };

    GaussianDistribution g2 = {
        .mu_x    = ((double)rand())/RAND_MAX * WINDOW_WIDTH*0.8 + WINDOW_WIDTH*0.1,
        .mu_y    = ((double)rand())/RAND_MAX * WINDOW_HEIGHT*0.8 + WINDOW_HEIGHT*0.1,
        .sigma_x = ((double)rand())/RAND_MAX * 40 + 10,
        .sigma_y = ((double)rand())/RAND_MAX * 40 + 10,
    };

    GaussianDistribution g3 = {
        .mu_x    = ((double)rand())/RAND_MAX * WINDOW_WIDTH*0.8 + WINDOW_WIDTH*0.1,
        .mu_y    = ((double)rand())/RAND_MAX * WINDOW_HEIGHT*0.8 + WINDOW_HEIGHT*0.1,
        .sigma_x = ((double)rand())/RAND_MAX * 40 + 10,
        .sigma_y = ((double)rand())/RAND_MAX * 40 + 10,
    };

    GaussianDistribution gaussian_distributions[3] = {g1,g2,g3};


    generate_gaussian_clusters_dataset(dataset, N, gaussian_distributions, 3);

    ////////////////////////////////////////////////////////////
    // k-Means Algorithm
    ////////////////////////////////////////////////////////////

    // 1. Initialization Phase

    const int k = 3;
    Point centroids[k];

    for(int i = 0; i < k; i++)
    {
        int selected_element = rand()%N;
        
        centroids[i].x = dataset[selected_element].x; 
        centroids[i].y = dataset[selected_element].y; 

    }

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
            else if (e.type == SDL_KEYDOWN) 
            {
                switch (e.key.keysym.sym) 
                {
                    case SDLK_UP:
                        
                       
                        // Classify Data
                        classify_dataset(dataset, N, centroids, k);

                        // Render k-Means algorithm state to SDL_Window
                       
                        // Clear Window
                        clear_window(&renderer);

                        draw_decision_boundaries(centroids, k, WINDOW_WIDTH, WINDOW_HEIGHT, &renderer);
                        draw_classified_dataset(dataset, N, &renderer);
                        draw_centroids(centroids, k, &renderer);

                        // Render all to screen                        
                        SDL_RenderPresent(renderer);
                        
                        // Recompute centroids
                        recompute_centroids(dataset,N,centroids,k);
                                                


                        break;

                    default:

                        break;
                }
            }
        }
    }
    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

