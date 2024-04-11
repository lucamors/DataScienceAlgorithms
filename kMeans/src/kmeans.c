#include "kmeans.h"
#include "gaussian_distribution.h"


/*
* Compute the eucliedean distance (i.e., L2 distance)
* between to Point (2D)
*/
double compute_euclidean_distance(Point p1, Point p2)
{
    return sqrt( (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y) );
}

/*
* Generate a dataset having two gaussian clusters 
*/
void generate_gaussian_clusters_dataset(Point* point_array, int counts, GaussianDistribution* g1, GaussianDistribution* g2)
{

    for (int i = 0; i < counts; i++)
    {
        
        Point p = {0,0,0};

        if(i > counts/2)
        {
            p.x = generate_gaussian(g1->mu_x,g1->sigma_x);
            p.y = generate_gaussian(g1->mu_y,g1->sigma_y);
        }
        else
        {
            p.x = generate_gaussian(g2->mu_x,g2->sigma_x);
            p.y = generate_gaussian(g2->mu_y,g2->sigma_y);
        }
        

        point_array[i] = p; 
    }

    return ;
    
}

/*
* Update centroid position
*/
void update_centroid(Point * point, double new_x, double new_y)
{

    point->x = new_x;
    point->y = new_y;

    return ;
}