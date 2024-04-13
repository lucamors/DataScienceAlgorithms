#include "gui.h"
#include <SDL.h>


/*
* Initialize SDL lib
*/
int init_sdl()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    return 0;
}


/*
* Create a window.
*/
SDL_Window* create_window( int width, int height)
{    
    SDL_Window* window = SDL_CreateWindow("k-Means Clustering", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!window) 
    {
        SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return NULL;
    }

    return window;
}

/*
* Create a rendered.
*/
SDL_Renderer* create_renderer(SDL_Window** ptr_window)
{
    // Create renderer for window

    SDL_Renderer* renderer = SDL_CreateRenderer(*ptr_window, -1,SDL_RENDERER_ACCELERATED);
    if (!renderer) 
    {
        SDL_Log("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(*ptr_window);
        SDL_Quit();
        return NULL;
    }

    return renderer;
}


/*
* Delete window content and set all to black.
*/
void clear_window(SDL_Renderer** ptr_renderer)
{
    SDL_SetRenderDrawColor(*ptr_renderer, 0, 0, 0, 255); // RGBA
    SDL_RenderClear(*ptr_renderer);

    return ;
}

/*
* Draw a centroid onto window.
*/
void draw_centroid(Point * centroid, SDL_Renderer** ptr_renderer, int red, int green, int blue)
{
    
    SDL_SetRenderDrawColor(*ptr_renderer, red, green, blue, 255); // RGBA
    SDL_Rect fillCentroid = {centroid->x, centroid->y, 10, 10};
    SDL_RenderFillRect(*ptr_renderer, &fillCentroid);

    return ;
}

/*
* Render classified dataset.
*/
void draw_classified_dataset(Point * dataset, int dataset_size, SDL_Renderer** ptr_renderer)
{
    for(int i = 0; i < dataset_size; i++)
    {
        int class = dataset[i]._class;
        SDL_SetRenderDrawColor(*ptr_renderer,  20*class*class, 40*class+10, 40, 150); // RGBA
        SDL_Rect cr = {dataset[i].x, dataset[i].y, 2, 2};
        SDL_RenderFillRect(*ptr_renderer, &cr);
    }
}

/*
* Render centroids dataset.
*/
void draw_centroids(Point * centroids, int k, SDL_Renderer** ptr_renderer)
{
    for(int i = 0; i < k; i++)
    {
        SDL_SetRenderDrawColor(*ptr_renderer, 255, 255, 255, 255); // RGBA
        SDL_Rect cr = {centroids[i].x, centroids[i].y, 10, 10};
        SDL_RenderFillRect(*ptr_renderer, &cr);
    }

    return ;
}

/*
* Render decision boundaries.
*/
void draw_decision_boundaries(Point * centroids, int k, int width, int height, SDL_Renderer** ptr_renderer)
{
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            Point p = {x,y,0};
            int class = classify_point(p,centroids,k);

            SDL_SetRenderDrawColor(*ptr_renderer,  20*class*class, 40*class+10, 40, 100); // RGBA
            SDL_Rect cr = {x, y, 1, 1};
            SDL_RenderFillRect(*ptr_renderer, &cr);
        }
    }

    return ;
}