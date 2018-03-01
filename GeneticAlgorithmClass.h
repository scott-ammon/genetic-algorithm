// ************************************************************************ //
// This class contains all functionality to run a genetic algorithm on a 
// population of ChromosomeClass objects
// ************************************************************************ //

#ifndef _GENETICALGORITHM_H_
#define _GENETICALGORITHM_H_

#include "ChromosomeClass.h"
#include "ParameterClass.h"

class GeneticAlgorithmClass
{
  private:
    int    populationSize;
    int    generations;
    double mutationPct;
    double crossoverPct;
    ChromosomeClass *population;

  public:
    // sets the population size
    bool initializePopulation(int &popSize,ParameterClass &param);

    // sets the number of iterations to use
    bool setGenerations(int &gen);

    // sets the % of population to mutate
    bool setMutation(double &mutation);

    // sets % of population to crossover
    bool setCrossover(double &crossover);

    // contains functionality to run the GA
    void runGeneticAlgorithm(ParameterClass &parameters);
    
    // functionality to mate the population and get next generation
    void selectionOp();

    // functionality to mutate a percentage of the population
    void mutationOp();

    // functionality to crossover on a percentage of population
    void crossoverOp();

    int getPopSize() const;
};

#endif
