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
    // genes

    // CONSTRUCTORS

    // METHODS
};


// FUNCTIONS
// randomizing Points position
// distributing the points in the cartesian plane
inline void distributing();

// how to choose the parents for the next generation
inline void selection();

// how to mutate the child if it hit the chance of mutating
inline void mutate();

// how to cross the genes of the two parents to create a new child agent
inline void crossing();

// evaluating the path, returns the sum of euclidean distances
inline double evaluation();

#endif