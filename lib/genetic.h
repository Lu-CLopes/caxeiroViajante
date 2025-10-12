#ifndef _GENETIC_H_
#define _GENETIC_H_


#include "point.h"


// CONSTANTS
const uint8_t AMOUNT_POINTS = 8;                // 8 or more
const int POPULATION = 200;                     // amount of AI agents
const uint8_t STAGNATE_GENERATIONS_MAX = 20;    // amount of sequential stagnate generations to stop the training
const uint8_t CHANCE_OF_MUTATION = 5;           // chance to mutate, in %


// AI AGENT
class ai_agent{
public:
    // ATTRIBUTES
    Point genes[AMOUNT_POINTS];

    // CONSTRUCTORS

    // METHODS
};


// FUNCTIONS
// distributing the points in the cartesian plane
inline void distributing();

// how to choose the parents for the next generation
inline void selection()
{
    // chosen method: Championship
}

// how to mutate the child if it hit the chance of mutating
inline void mutate(Point genes[])
{}

// checks arr[start] up to arr[end] for target
inline bool arrayContains(Point arr[], char target, int start, int end)
{
    int temp;
    for(temp = start; temp<=end; temp++)
    {
        if(arr[temp].name == target)
            return true;
    }

    return false;
}

// how to cross the genes of the two parents to create a new child agent
inline ai_agent crossing(ai_agent Mother, ai_agent Father)
{
    //  chosen method: Ordered Crossover
    int m, f, up = 0;   // mother, father and used_points counter
    ai_agent child;
    char used_points[AMOUNT_POINTS/2];

    // first half of mother is used
    for(m=0; m<AMOUNT_POINTS/2; m++)
    {
        child.genes[m] = Mother.genes[m];
        used_points[up++] = Mother.genes[m].name;
    }

    // the other elements are taken from the father in the order they show up
    for(f=0; f<AMOUNT_POINTS || m<AMOUNT_POINTS; f++)
    {
        Point temp = Father.genes[f];

        if(!arrayContains(child.genes, temp.name, 0, (int) AMOUNT_POINTS/2))
        {
            child.genes[m++] = Father.genes[f];
            used_points[up++] = Father.genes[f].name;
        }
    }

    // possibility of mutation
    // if it mutates, call the function
    uint8_t chance; // random number from 0-99

    if(chance < CHANCE_OF_MUTATION)
        mutate(child.genes);

    // return the resulting point
    return child;
}

// evaluating the path, returns the sum of euclidean distances
inline double evaluation(Point genes[AMOUNT_POINTS])
{
    double sum = 0;
    int i;

    for(i=0; i<AMOUNT_POINTS-1;i++)
        sum += genes[i].d2op(genes[i+1]);

    return sum;
}

// environment functions
// create benchmark environment
inline void init_benchmark(Point points[])
{
    int i;
    const int RADIUS = 100;
    double angle = 0.0;
    const double angular_distance = (2*PI)/AMOUNT_POINTS;
    char name = 'A';

    for(i=0; i<AMOUNT_POINTS; i++)
    {
        points[i].setInfo(RADIUS* cos(angle), RADIUS* sin(angle), name);

        angle += angular_distance;
        name++;
    }

    return;
}

#endif