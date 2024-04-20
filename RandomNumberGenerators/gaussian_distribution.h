#ifndef GAUSSIAN_DISTRIBUTION_H
#define GAUSSIAN_DISTRIBUTION_H

#include <math.h>
#include <stdlib.h>


/*
* A struct that defines a 2D Gaussian Distribution
*/
typedef struct GaussianDistribution{

    double mu_x;
    double mu_y;
    double sigma_x;
    double sigma_y;


} GaussianDistribution;


/*
* Generate a gaussian distributed double with a certain
* mean and sigma using the Box-Muller Algorithm.
* the stdlib rand() function is used for generating U1 and U2.
*/
double generate_gaussian(double mean, double sigma)
{
    double U1 = ((double)rand())/RAND_MAX;
    double U2 = ((double)rand())/RAND_MAX;

    return ( sigma * sqrt(-2*log(U1)) * cos(2.0*M_PI*U2) ) + mean;
}

/*
* Generate a dataset having "number_of_distributions" gaussian clusters 
*
*/
void generate_gaussian_clusters_dataset(Point* point_array, int counts, GaussianDistribution* gaussian_distribution_array, int number_of_distributions)
{

    for (int i = 0; i < counts; i++)
    {
        
        int selected_distribution = i%number_of_distributions;
        
        // Draw a sample from the selected distribution
        // new point class is initialized to -1 as point is unclassified
        Point p = {0,0,-1};
        p.x = generate_gaussian(gaussian_distribution_array[selected_distribution].mu_x,gaussian_distribution_array[selected_distribution].sigma_x);
        p.y = generate_gaussian(gaussian_distribution_array[selected_distribution].mu_y,gaussian_distribution_array[selected_distribution].sigma_y);
        
        // Save point to array
        point_array[i] = p; 
    }

    return ;
    
}


#endif