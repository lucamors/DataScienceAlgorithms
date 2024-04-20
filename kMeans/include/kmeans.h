#ifndef KMEANS_H
#define KMEANS_H

#include "point.h"

//----------------------------------------------------//

typedef enum {
    
    FORGY,
    RANDOM_PARTITION

} initialization_method; 

//----------------------------------------------------//

double compute_euclidean_distance(Point, Point);

//----------------------------------------------------//

void initialize_centroids(Point*, int, Point*, int, initialization_method);

//----------------------------------------------------//

void classify_dataset(Point* , int , Point* , int);

//----------------------------------------------------//

void recompute_centroids(Point* , int , Point* , int);

//----------------------------------------------------//

int classify_point(Point, Point*, int);


#endif