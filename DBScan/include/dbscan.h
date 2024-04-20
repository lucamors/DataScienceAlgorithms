#ifndef DBSCAN_H
#define DBSCAN_H

#include "point.h"
#include "vector.h"

typedef enum {

    BRUTE

} RangeQueryType;

//----------------------------------------------------//

Vector* find_neighbors(Point * database, int N, Point point, double eps, RangeQueryType rqtype);

//----------------------------------------------------//

double compute_euclidean_distance(Point p1, Point p2);


#endif