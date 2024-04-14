#include <float.h>

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
void generate_gaussian_clusters_dataset(Point* point_array, int counts, GaussianDistribution* gaussian_distribution_array, int number_of_distributions)
{

    for (int i = 0; i < counts; i++)
    {
        

        int selected_distribution = i%number_of_distributions;
        
        // Draw a sample from the selected distribution
        Point p = {0,0,0};
        p.x = generate_gaussian(gaussian_distribution_array[selected_distribution].mu_x,gaussian_distribution_array[selected_distribution].sigma_x);
        p.y = generate_gaussian(gaussian_distribution_array[selected_distribution].mu_y,gaussian_distribution_array[selected_distribution].sigma_y);
        
        // Set class to -1 as point is unclassified
        p._class = -1;
        point_array[i] = p; 
    }

    return ;
    
}

/*
* Classify the dataset using the k-Means assignement rule.
*/
void classify_dataset(Point* dataset, int dataset_size, Point* centroids, int k)
{
    // 2. Assignement step
    for(int i = 0; i < dataset_size; i++)
    {
        // Assign dataset element to the closest class                            
        dataset[i]._class = classify_point(dataset[i], centroids, k); 
    }

    return ;
}

/*
* Recompute centroids position
*/
void recompute_centroids(Point* dataset, int dataset_size, Point* centroids, int k)
{
    // Reset centroids position
    for(int i = 0; i < k; i++)
    {
        centroids[i].x = 0;
        centroids[i].y = 0;

        // Here we can use Point _class member as element counts
        centroids[i]._class = 0;
    }


    for(int i = 0; i < dataset_size; i++)
    {

        int centroid_id = dataset[i]._class;

        centroids[centroid_id].x += dataset[i].x;
        centroids[centroid_id].y += dataset[i].y;
        centroids[centroid_id]._class += 1;
    }

    // Compute means
    for(int i = 0; i < k; i++)
    {
        centroids[i].x /= centroids[i]._class;
        centroids[i].y /= centroids[i]._class;

        // Assign centroid to its class for consistency
        centroids[i]._class = i;
    }


    return ;
}

/*
* Classify a point given an array of centroids
*/
int classify_point(Point point, Point* centroids, int k)
{
        int current_element_class;
        // Set current dataset element to double maximum allowed value;
        double minimum_distance = DBL_MAX;
        
        // Compute the Euclidean distance between the current element and all the centorids
        for(int j = 0; j < k; j++)
        {
            double current_distance = compute_euclidean_distance(centroids[j], point);
            
            if(current_distance < minimum_distance)
            {
                minimum_distance = current_distance;
                current_element_class = j;
            }
            
        }

        return current_element_class;
}