#ifndef KMEANS_H
#define KMEANS_H
//----------------------------------------------------//

typedef struct GaussianDistribution{

    double mu_x;
    double mu_y;
    double sigma_x;
    double sigma_y;


} GaussianDistribution;

//----------------------------------------------------//

typedef struct Point{

    double x;
    double y;
    int _class;


} Point;

//----------------------------------------------------//

double compute_euclidean_distance(Point, Point);

//----------------------------------------------------//

void generate_gaussian_clusters_dataset(Point*, int, GaussianDistribution*, GaussianDistribution*);

//----------------------------------------------------//

void update_centroid(Point *, double, double);

#endif