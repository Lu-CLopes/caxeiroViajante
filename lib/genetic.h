#ifndef _GENETIC_H_
#define _GENETIC_H_


#include "point.h"
#include <cfloat>


// CONSTANTS
const int AMOUNT_POINTS = 20;                            // 8 or more
const int POPULATION = 480;                                  // amount of AI agents
const int GENERATIONS_MAX = 10000;                          // max amount of generations
//const int STAGNATE_GENERATIONS_MAX = GENERATIONS_MAX/10;     // amount of sequential stagnate generations to stop the training
const uint8_t CHANCE_OF_MUTATION = 5;                      // chance to mutate, in %
const uint8_t CHAMPIONSHIP_SIZE = 3;                        // amount of participants in each championship
//const int PARENTS_POPULATION = POPULATION/CHAMPIONSHIP_SIZE;


// AI AGENT
class ai_agent{
public:
    // ATTRIBUTES
    Point genes[AMOUNT_POINTS];

    // CONSTRUCTORS
    ai_agent(){}

    ai_agent(Point points[AMOUNT_POINTS]){
        int i;

        for(i=0; i<AMOUNT_POINTS; i++)
            genes[i] = points[i];
    }

    // METHODS
    void setGenes(Point points[AMOUNT_POINTS])
    {
        int i;

        for(i=0; i<AMOUNT_POINTS; i++)
            genes[i] = points[i];
    }
};


// FUNCTIONS

// evaluating the path, returns the sum of euclidean distances
inline double evaluation(Point genes[AMOUNT_POINTS])
{
    double sum = 0;
    int i;

    for(i=0; i<AMOUNT_POINTS-1;i++)
        sum += genes[i].d2op(genes[i+1]);

    return sum;
}

// how to choose the parents for the next generation
inline void selection(ai_agent population[], ai_agent winners[], int pop)
{
    // chosen method: Championship

    // for the total population, do a championship of CHAMPIONSHIP_SIZE individuals
    for (int i = 0; i < pop; i += CHAMPIONSHIP_SIZE)
    {
        ai_agent champ_winner;
        double bestFitness = DBL_MAX;  // initially "infinite", max value of double

        for (int j = 0; j < CHAMPIONSHIP_SIZE /*&& (i + j) < POPULATION*/; j++) // we don't need the commented part if we
        {                                                                       // guarantee the pop. is divisible by champ_size
            int idx = i + j;
            double fit = evaluation(population[idx].genes);

            if (fit < bestFitness)
            {
                bestFitness = fit;
                champ_winner = population[idx];
            }
        }
        winners[i/CHAMPIONSHIP_SIZE] = champ_winner;
    }
}

// how to mutate the child if it hit the chance of mutating
inline void mutate(ai_agent *agent)
{
    // chosen method: Swap Mutation
    int i,j;

    // choose index from 0 to AMOUNT_POINTS-1 randomly and swap with the next index
    i = rand() % (AMOUNT_POINTS-1); // 1-18

    // circular motion to get next index
    j = (i + 1) % AMOUNT_POINTS;

    // swap adjacent points
    std::swap(agent->genes[i], agent->genes[j]);
}

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
inline ai_agent crossing(ai_agent Mother, ai_agent Father, uint8_t mut, bool useInverter)
{
    //  chosen method: Ordered Crossover
    int m, f;   // mother, father and used_points counter
    ai_agent child;

    // first half of mother is used
    for(m=0; m<AMOUNT_POINTS/2; m++)
        child.genes[m] = Mother.genes[m];

    // now trash can't corrupt results
    for(m=4; m<AMOUNT_POINTS; m++)
        child.genes[m].name = 0;

    m=4;

    if(useInverter)
    {
        // before using the father genes, we can see if the two parents go on the same direction
        int i, j;
        int m_init= 0, f_init = 0, r_init = 0;

        // finding mother's initial gene on father's genes
        for(i=0; i<AMOUNT_POINTS; i++)
        {
            if(Father.genes[i].name == Mother.genes[0].name)
            {
                f_init = i;
                break;
            }
        }

        // creating the reversed father
        ai_agent rethaF = Father;
        for(i=1; i<AMOUNT_POINTS/2; i++)
            std::swap(rethaF.genes[i], rethaF.genes[AMOUNT_POINTS-i]);
        r_init = AMOUNT_POINTS-1-f_init;

        // evaluating best partner
        int f_points = 0, r_points=0;

        for(i=1; i<AMOUNT_POINTS; i++)
        {
            for(j=1; j<AMOUNT_POINTS; j++)
            {
                if(Mother.genes[(m_init+i)%AMOUNT_POINTS].name == Father.genes[(f_init+j)%AMOUNT_POINTS].name)
                {
                    f_points += j-i < 0? 0 : j-i;
                    break;
                }
            }
            
            for(j=1; j<AMOUNT_POINTS; j++)
            {
                if(Mother.genes[(m_init+i)%AMOUNT_POINTS].name == rethaF.genes[(r_init+j)%AMOUNT_POINTS].name)
                {
                    f_points += j-i < 0? 0 : j-i;
                    break;
                }
            }
        }


        if(r_points < f_points)
        {
            // the other elements are taken from the rethaf in the order they show up
            for(f=0; m<AMOUNT_POINTS || f<AMOUNT_POINTS; f++)
            {
                Point temp = rethaF.genes[f];

                if(!arrayContains(child.genes, temp.name, 0, (int) AMOUNT_POINTS/2-1))
                    child.genes[m++] = temp;
            }
        }
        else
        {
            // the other elements are taken from the father in the order they show up
            for(f=0; m<AMOUNT_POINTS || f<AMOUNT_POINTS; f++)
            {
                Point temp = Father.genes[f];

                if(!arrayContains(child.genes, temp.name, 0, (int) AMOUNT_POINTS/2-1))
                    child.genes[m++] = temp;
            }
        }
    
    }
    else
    {
        // the other elements are taken from the father in the order they show up
        for(f=0; m<AMOUNT_POINTS || f<AMOUNT_POINTS; f++)
        {
            Point temp = Father.genes[f];

            if(!arrayContains(child.genes, temp.name, 0, (int) AMOUNT_POINTS/2-1))
                child.genes[m++] = temp;
        }
    }

    // possibility of mutation
    int chance = rand()%100;
    if(chance < mut)
        mutate(&child);

    // return the resulting point
    return child;
}

inline void shuffle(Point points[AMOUNT_POINTS])
{
    int i;

    for(i=1; i<AMOUNT_POINTS; i++)
    {
        int temp = 0;
        temp = (rand() % (AMOUNT_POINTS-1))+1;  // 1-19

        if(temp != i)
            std::swap(points[i], points[temp]);
    }
}

// selects the best agent on the 
inline ai_agent bestAgent(ai_agent agents[], double *eval, int pop)
{
    int i;
    double comp = DBL_MAX;
    double temp;
    int id = 0;

    for(i=0; i<pop; i++)
    {
        temp = evaluation(agents[i].genes);
        if(temp < comp)
        {
            comp = temp;
            id = i;
            if(eval != NULL)
                *eval = temp;
        }
    }

    return agents[id];
}

inline void copyGen(ai_agent dst[], ai_agent src[], int pop)
{
    int i;

    for(i=0; i<pop; i++)
        dst[i] = src[i];
}

inline bool compGens(ai_agent curr[], ai_agent last[], int pop)
{
    int i, j;

    for(i=0; i<pop; i++)
        for(j=0; j<AMOUNT_POINTS; j++)
            if(!curr[i].genes[j].isEqualTo(last[i].genes[j]))
                return false;

    return true;
}

inline void proliferation(ai_agent population[], ai_agent parents[], int pop, uint8_t mut, bool useInverter)
{
    int i, j;

    for(i=0; i<pop/CHAMPIONSHIP_SIZE; i+=2)
    {
        for(j=0; j<2*CHAMPIONSHIP_SIZE; j+=2)
        {
            population[3*i+j] =     crossing(parents[j], parents[j+1], mut, useInverter);
            population[3*i+j+1] =   crossing(parents[j+1], parents[j], mut, useInverter);
        }
    }

    return;
}

// environment functions
// create benchmark environment
inline void init_benchmark(Point points[])
{
    int i;
    const int RADIUS = 300;
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

// create random environment
inline void init_random(Point points[])
{
    int i;
    char name = 'A';

    for(i=0; i<AMOUNT_POINTS; i++)
        points[i].setInfo(rand()%901 - 450, rand()%601 - 300, name++);

    return;
}

// TRAINING FUNCTION
inline void train(ai_agent agents[], Point points[AMOUNT_POINTS], Point saved[500][AMOUNT_POINTS], int *gens, int pop, int gnrt, uint8_t mut, bool useInverter)
{
    int i, stagCount = 0, savedCount = 0;
    bool notStagnate = true;
    ai_agent lastGen[pop];
    ai_agent currGen[pop];
    ai_agent currParents[pop/CHAMPIONSHIP_SIZE];
    double evalL = 0.0, evalC = 1.0;
    int currMut = mut;

    // initial config
    for(i=0; i<pop; i++)
    {
        agents[i].setGenes(points);
        shuffle(agents[i].genes);
    }
    copyGen(currGen, agents, pop);


    // main loop
    for(i=0; i<gnrt && notStagnate; i++)
    {
        selection(currGen, currParents, pop);

        copyGen(lastGen, currGen, pop);

        // DYNAMIC MUTATION CHANCE, avoids plateaus
        if(stagCount>1)
            currMut = mut + stagCount/2;
        proliferation(currGen, currParents, pop, currMut, useInverter);

        // check if stagnate
        ai_agent trash = bestAgent(lastGen, &evalL, pop);
        trash = bestAgent(currGen, &evalC, pop);

        if(evalL == evalC)
        {
            if(++stagCount >= gnrt/10)
                notStagnate = false;
        }
        else
            stagCount = 0;

        // shuffling the agents helps the genetic variablility by making agents compete with non-brothers
        // does it help? not shuffling allows for multiple strategies to develop at the same time
        int shuffle_index;

        for(shuffle_index=0; shuffle_index<pop; shuffle_index++)
        {
            int temp = rand() % pop;

            if(temp != shuffle_index)
                std::swap(currGen[shuffle_index], currGen[temp]);
        }

        // only saves 500 gens
        if(i%(gnrt/500) == 0)
        {

            ai_agent best = bestAgent(currGen, NULL, pop);
            int j;

            for(j=0; j<AMOUNT_POINTS; j++)
                saved[savedCount][j] = best.genes[j];

            savedCount++;
        }
    }

    // because of the i++ at the end of the loop, I don't need to add 1 to this variable
    *gens = i;

    return;
}

#endif