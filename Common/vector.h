#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>

#include "point.h"

typedef struct Vector{

    Point **array;
    int size;
    int capacity;

} Vector;

/*
* Create a dynamic array
*/
static Vector* create_vector()
{
    int capacity = 10;
    Vector *vector = (Vector*)malloc(sizeof(Vector)); 

    if(vector == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    vector->array = (Point**)malloc(capacity * sizeof(Point*));
    if(vector->array == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    vector->size = 0;
    vector->capacity = capacity;

    return vector;
}

/*
* Resize the vector with a new capacity
*/
static void resize_vector(Vector* vector, int new_capacity)
{
    vector->array = (Point**)realloc(vector->array, new_capacity * sizeof(Point*));
    if (vector->array == NULL) 
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    vector->capacity = new_capacity;
}

/*
*   
*/
static void vector_push_back(Vector* vector, Point* element)
{
    if(vector->size >= vector->capacity)
    {
        resize_vector(vector, vector->capacity * 2);
    }

    vector->array[vector->size++] = element;
}


#endif