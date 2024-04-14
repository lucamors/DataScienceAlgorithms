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

typedef enum {
    
    FORGY,
    RANDOM_PARTITION

} initialization_method; 

//----------------------------------------------------//

double compute_euclidean_distance(Point, Point);

//----------------------------------------------------//

void generate_gaussian_clusters_dataset(Point*, int, GaussianDistribution*, int);

//----------------------------------------------------//

void initialize_centroids(Point*, int, Point*, int, initialization_method);

//----------------------------------------------------//

void classify_dataset(Point* , int , Point* , int);

//----------------------------------------------------//

void recompute_centroids(Point* , int , Point* , int);

//----------------------------------------------------//

int classify_point(Point, Point*, int);


#endif