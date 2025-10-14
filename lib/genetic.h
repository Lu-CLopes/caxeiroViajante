#ifndef _GENETIC_H_
#define _GENETIC_H_

#include "point.h"
#include <vector>
using std::vector;

// CONSTANTS
const uint8_t AMOUNT_POINTS = 8;             // 8 or more
const int POPULATION = 200;                  // amount of AI agents
const uint8_t STAGNATE_GENERATIONS_MAX = 20; // amount of sequential stagnate generations to stop the training
const uint8_t CHANCE_OF_MUTATION = 5;        // chance to mutate, in %
const uint8_t CHAMPIONSHIP_SIZE = 3;

// AI AGENT
class ai_agent
{
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
inline vector<ai_agent> selection(vector<ai_agent> &population)
{
    // chosen method: Championship
    vector<ai_agent> winners; // vector of winners of each championship
    double totalFitness = 0.0;

    // calculate the max fitness of the population
    for (int i = 0; i < (int)population.size(); i++)
    {
        totalFitness += evaluation(population[i].genes);
    }

    // for the total population, do a championship of CHAMPIONSHIP_SIZE individuals
    for (int i = 0; i < (int)population.size(); i += CHAMPIONSHIP_SIZE)
    {
        ai_agent champ_winner;
        double bestFitness = totalFitness; // setting each championship

        for (int j = 0; j < CHAMPIONSHIP_SIZE && (i + j) < (int)population.size(); j++)
        {
            int idx = i + j;
            double fit = evaluation(population[idx].genes);

            if (fit < bestFitness)
            {
                bestFitness = fit;
                champ_winner = population[idx];
            }
        }
        winners.push_back(champ_winner);
    }

    return winners;
}

// how to mutate the child if it hit the chance of mutating
inline void mutate(ai_agent &agent)
{
    // chosen method: Swap Mutation
    int chance = rand() % 100; // random number from 0 to 99 for porcentage

    if (chance < CHANCE_OF_MUTATION)
    {
        // choose index from 0 to 7 randomly and swap with the next index
        int i = rand() % AMOUNT_POINTS;

        // circular motion to get next index
        int j = (i + 1) % AMOUNT_POINTS;

        // swap adjacent points
        Point temp = agent.genes[i];
        agent.genes[i] = agent.genes[j];
        agent.genes[j] = temp;
    }
}

// how to cross the genes of the two parents to create a new child agent
inline ai_agent crossing(ai_agent Mother, ai_agent Father)
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

    for (i = 0; i < AMOUNT_POINTS - 1; i++)
        sum += genes[i].d2op(genes[i + 1]);

    return sum;
}

#endif