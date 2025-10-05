#ifndef _GENETIC_H_
#define _GENETIC_H_


#include "point.h"


// CONSTANTS
const uint8_t AMOUNT_POINTS = 8;    // 8 or more
const uint8_t POPULATION = 0;       // amount of AI agents


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
inline void selection();

// how to mutate the child if it hit the chance of mutating
inline void mutate();

// how to cross the genes of the two parents to create a new child agent
inline Point crossing(Point Mother, Point Father)
{
    //  chosen method: Ordered Crossover

    // first half of mother is used
    // the other elements are taken from the father in the order they show up

    // possibility of mutation
    // if it mutates, call the function

    // return the resulting point
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

#endif