#ifndef GAUSSIAN_DISTRIBUTION_H
#define GAUSSIAN_DISTRIBUTION_H

#include <math.h>
#include <stdlib.h>

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


#endif