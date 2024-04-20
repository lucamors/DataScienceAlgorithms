#include <math.h>
#include <stdio.h>
#include <float.h>
#include <stdlib.h>

#include "kmeans.h"
#include "point.h"


/*
* Compute the eucliedean distance (i.e., L2 distance)
* between to Point (2D)
*/
double compute_euclidean_distance(Point p1, Point p2)
{
    return sqrt( (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y) );
}

/*
* Initialize centroid position using the specified initialization method
*/
void initialize_centroids(Point* centroids, int k, Point* dataset, int dataset_size, initialization_method method)
{
    switch(method)
    {
        case FORGY:
            for(int i = 0; i < k; i++)
            {
                int selected_element = rand()%dataset_size;
                
                centroids[i].x = dataset[selected_element].x; 
                centroids[i].y = dataset[selected_element].y; 

            }
            break;

        default:
            printf("No valid initialization method provided. Exit.");
            exit(-1);
            break;
    }
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
        dataset[i].label = classify_point(dataset[i], centroids, k); 
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

        // Here we can use Point 'label' member as element counter
        centroids[i].label = 0;
    }


    for(int i = 0; i < dataset_size; i++)
    {

        int centroid_id = dataset[i].label;

        centroids[centroid_id].x += dataset[i].x;
        centroids[centroid_id].y += dataset[i].y;
        centroids[centroid_id].label += 1;
    }

    // Compute means
    for(int i = 0; i < k; i++)
    {
        centroids[i].x /= centroids[i].label;
        centroids[i].y /= centroids[i].label;

        // Assign centroid.label back to its class for consistency (optional)
        centroids[i].label = i;
    }

    return ;
}

/*
* Classify a point given an array of centroids
*/
int classify_point(Point point, Point* centroids, int k)
{
        int current_elementlabel;
        // Set current dataset element to double maximum allowed value;
        double minimum_distance = DBL_MAX;
        
        // Compute the Euclidean distance between the current element and all the centorids
        for(int j = 0; j < k; j++)
        {
            double current_distance = compute_euclidean_distance(centroids[j], point);
            
            if(current_distance < minimum_distance)
            {
                minimum_distance = current_distance;
                current_elementlabel = j;
            }
            
        }

        return current_elementlabel;
}