
#ifndef GUI_H
#define GUI_H

#include <SDL.h>
#include "point.h"

int init_sdl();

SDL_Window* create_window(int, int);

SDL_Renderer* create_renderer(SDL_Window**);

void clear_window(SDL_Renderer**);

void draw_centroid(Point*, SDL_Renderer**, int, int, int);

void draw_classified_dataset(Point *, int, SDL_Renderer**);

void draw_centroids(Point *, int, SDL_Renderer**);

void draw_decision_boundaries(Point*, int, int, int, SDL_Renderer**);

#endif