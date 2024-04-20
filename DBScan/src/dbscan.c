#include <math.h>
#include "dbscan.h"
#include "point.h"
#include "vector.h"

/*
* Compute the eucliedean distance (i.e., L2 distance)
* between to Point (2D)
*/
double compute_euclidean_distance(Point p1, Point p2)
{
    return sqrt( (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y) );
}

/*
*  Count the neighbors of a point in a dataset
*/
Vector* find_neighbors(Point * database, int N, Point point, double eps, RangeQueryType rqtype)
{

    Vector* neighbors = create_vector();

    switch (rqtype)
    {
        case BRUTE:

            
            for(int i = 0; i < N; i++)
            {

                
                if(compute_euclidean_distance(database[i],point) < eps)
                {
                    vector_push_back(neighbors, &database[i]);
                }
                
            }

            break;
        
        default:
            break;
    }


    return neighbors;
}
