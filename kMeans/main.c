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

    // Set window color to black
    clear_window(&renderer);
  
    // Generate a random gaussian distribution
    ////////////////////////////////////////////////////////////

    // Init random number generator
    srand(time(NULL));

    const int N = 50000;
    Point dataset[N];

    GaussianDistribution g1 = {
        .mu_x    = ((double)rand())/RAND_MAX * WINDOW_WIDTH,
        .mu_y    = ((double)rand())/RAND_MAX * WINDOW_HEIGHT,
        .sigma_x = ((double)rand())/RAND_MAX * 40 + 10,
        .sigma_y = ((double)rand())/RAND_MAX * 40 + 10,
    };

    GaussianDistribution g2 = {
        .mu_x    = ((double)rand())/RAND_MAX * WINDOW_WIDTH*0.2 + WINDOW_WIDTH*0.1,
        .mu_y    = ((double)rand())/RAND_MAX * WINDOW_HEIGHT*0.2 + WINDOW_HEIGHT*0.1,
        .sigma_x = ((double)rand())/RAND_MAX * 40 + 10,
        .sigma_y = ((double)rand())/RAND_MAX * 40 + 10,
    };


    generate_gaussian_clusters_dataset(dataset, N, &g1, &g2);

    // k-Means Algorithm
    ////////////////////////////////////////////////////////////

    // 1. Initialization Phase
    int i1 = (int)(((double)rand())/RAND_MAX*N);
    int i2 = (int)(((double)rand())/RAND_MAX*N);
    
    Point centroid1 = { .x = dataset[i1].x, .y = dataset[i1].y };
    Point centroid2 = { .x = dataset[i2].x, .y = dataset[i2].y };

    
    for (size_t j = 0; j < 5; j++)
    {
        // 2. Assignement step
        for(int i = 0; i < N; i++)
        {
            // Computing distance between two centroids
            double d1 = sqrt( (centroid1.x-dataset[i].x)*(centroid1.x-dataset[i].x) + (centroid1.y-dataset[i].y)*(centroid1.y-dataset[i].y) );
            double d2 = sqrt( (centroid2.x-dataset[i].x)*(centroid2.x-dataset[i].x) + (centroid2.y-dataset[i].y)*(centroid2.y-dataset[i].y) );

            // Assign point to the closest cluster
            if( d1 > d2)
            {
                dataset[i]._class = 2; 
            }
            else
            {
                dataset[i]._class = 1;
            }
        }
        
        // 3. Centroid recompute step
        float mean1x = 0;
        float mean1y = 0;
        int c1 = 0;

        float mean2x = 0;
        float mean2y = 0;
        int c2 = 0;

        for(int i = 0; i < N; i++)
        {
            if(dataset[i]._class == 1)
            {
                mean1x += dataset[i].x;
                mean1y += dataset[i].y;
                c1++;
                // Set drawing color to blue
                SDL_SetRenderDrawColor(renderer, 150,0 , 0, 255); // RGBA
            }
            else
            {
                mean2x += dataset[i].x;
                mean2y += dataset[i].y;
                c2++; 
                SDL_SetRenderDrawColor(renderer, 0,0 , 150, 255); // RGBA
            }

            // Draw a filled rectangle
            SDL_Rect cr = {dataset[i].x, dataset[i].y, 1, 1};
            SDL_RenderFillRect(renderer, &cr);
        }

        // Updating centroid
        update_centroid(&centroid1, mean1x/c1, mean1y/c1);
        update_centroid(&centroid2, mean2x/c2, mean2y/c2);

        // Draw new centroid to canvas
        for (int k = 0; k < WINDOW_WIDTH; k++)
        {
            for(int l = 0; l < WINDOW_HEIGHT; l++)
            {
                double d1 = sqrt( (centroid1.x-k)*(centroid1.x-k) + (centroid1.y-l)*(centroid1.y-l) );
                double d2 = sqrt( (centroid2.x-k)*(centroid2.x-k) + (centroid2.y-l)*(centroid2.y-l) );

                // Assign point to the closest cluster
                if( d1 < d2)
                {
                    SDL_SetRenderDrawColor(renderer, 50,0 , 0, 100);
                    SDL_Rect cr = {k, l, 1, 1};
                    SDL_RenderFillRect(renderer, &cr);
                }
                else
                {
                    SDL_SetRenderDrawColor(renderer, 0,0 , 50, 100);
                    SDL_Rect cr = {k, l, 1, 1};
                    SDL_RenderFillRect(renderer, &cr);
                }
            }
        }

        for(int i = 0; i < N; i++)
        {
            if(dataset[i]._class == 1)
            {
                SDL_SetRenderDrawColor(renderer, 150,0 , 0, 255); // RGBA
    
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0,0 , 150, 255); // RGBA
            }

            // Draw a filled rectangle
            SDL_Rect cr = {dataset[i].x, dataset[i].y, 1, 1};
            SDL_RenderFillRect(renderer, &cr);
        }
        
        draw_centroid(&centroid1, &renderer, 255,0,0);
        draw_centroid(&centroid2, &renderer, 0,0,255);

        SDL_RenderPresent(renderer);

        SDL_Delay(2000);
        clear_window(&renderer);
    }
    
    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

