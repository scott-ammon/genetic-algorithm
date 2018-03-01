// ************************************************************************ //
// Genetic Algorithm Class source code
// ************************************************************************ //

#include <iostream>
using namespace std;

#include <fstream>
#include <exception>
using std::fstream;

#include "ChromosomeClass.h"
#include "GeneticAlgorithmClass.h"
#include "GlobalConstants.h"

bool GeneticAlgorithmClass::initializePopulation(int &popSize,
                                                 ParameterClass &param)
{
  while(popSize <= 0 || popSize > MAX_POPULATION)
  {
    cout << "ERROR: Population size invalid." << endl;
    cout << "Input population size: ";
    cin  >> popSize;
  }

  populationSize = popSize;
  population = new ChromosomeClass[populationSize];
    
  int i;                    // counter for population
  int g;                    // counter for genes
  double *singleChromosome; // chromosome to be initialized
  double *loBounds;         // minimum values for this chromosome
  double *upBounds;         // maximum values for this chromosome
    
  singleChromosome = new double[NUM_GENES];
  loBounds         = new double[NUM_GENES];
  upBounds         = new double[NUM_GENES];
   
  // Define lower bounds for each gene
  loBounds[LENGTH_INDEX] = param.getMinLength(); 
  loBounds[BEAM_INDEX] = param.getMinBeam();
  loBounds[DRAFT_INDEX] = param.getMinDraft();
  loBounds[BLOCK_COEFF_INDEX] = MIN_BLOCK_COEFF;

  // Define upper bounds for each gene
  upBounds[LENGTH_INDEX] = param.getMaxLength(); 
  upBounds[BEAM_INDEX] = param.getMaxBeam();
  upBounds[DRAFT_INDEX] = param.getMaxDraft();
  upBounds[BLOCK_COEFF_INDEX] = MAX_BLOCK_COEFF;

  for(i = 0; i < populationSize; i++)
  {
    singleChromosome[LENGTH_INDEX] = chooseDouble(param.getMinLength(),
                                       param.getMaxLength());
    singleChromosome[BEAM_INDEX]   = chooseDouble(param.getMinBeam(),
                                       param.getMaxBeam());
    singleChromosome[DRAFT_INDEX]  = chooseDouble(param.getMinDraft(),
                                       param.getMaxDraft());
    singleChromosome[BLOCK_COEFF_INDEX] = chooseDouble(MIN_BLOCK_COEFF,
                                                       MAX_BLOCK_COEFF);
    
    // create a chromosome using the random values and upper/lower bounds
    population[i].setChromosome(singleChromosome,loBounds,upBounds);
  }

    return(1);
}

bool GeneticAlgorithmClass::setGenerations(int &gen)
{
  while( gen < 0)
  {
    cout << "ERROR: Generations not valid." << endl;
    cout << "Input number of generations: ";
    cin  >> gen;
  }  
  if(gen > MAX_GENERATIONS)
  {
    cout << "ERROR: Generations exceeds maximum allowable." << endl
         << "Max allowed is: " << MAX_GENERATIONS           << endl;
         generations = MAX_GENERATIONS;
    cout << "Number of generations set to: " << MAX_GENERATIONS << endl;
  }
  else
  {
    generations = gen;
  } 
  return(1);
}

bool GeneticAlgorithmClass::setMutation(double &mutation)
{
  while(mutation < 0 || mutation > MAX_MUTATION)
  {
    cout << "ERROR: Invalid Mutation Percentage." << endl;
    cout << "Input Mutation Percent (0 to 0.1): ";
    cin  >> mutation;
  }
    mutationPct = mutation;
    return(1);
}

bool GeneticAlgorithmClass::setCrossover(double &crossover)
{
  while(crossover < 0 || crossover > MAX_CROSSOVER)
  {
    cout << "ERROR: Invalid Crossover Percentage." << endl;
    cout << "Input Crossover Percent (0 to 1): ";
    cin  >> crossover;
  }
  crossoverPct = crossover;
  return(1);
}

int GeneticAlgorithmClass::getPopSize() const
{
  return(populationSize);
}

void GeneticAlgorithmClass::runGeneticAlgorithm(ParameterClass &parameters)
{
  cout.unsetf(ios::floatfield);
  cout.setf(ios::showpoint);
  cout.precision(1);
  cout << fixed;

  int    i;             // loop variable
  bool   stop = false;  // stop variable for while-loop
  int    counter = 1;   // count through the generations
  int    print   = 0;   // print to screen variable

  ofstream outFile;     // create a text file for output from the GA
  string   GAoutput = "GAoutput.txt";
  
  outFile.open(GAoutput.c_str());

  if(outFile.fail())
  {
    cout << "ERROR: Unable to open " << GAoutput << endl
         << "Populations will not be written to file." << endl;
  }       
  else
  {
    cout << "Population will be printed to " << GAoutput << endl;
  }
  cout << "Print Populations To Screen? (1-yes, 2-no): ";
  cin  >> print;

  while(!stop)
  {
    if(print == 1)
    {
      // Evaluate Fitness of Each Chromosome
      cout << "*****************************************************"
           << endl << "Generation Number " << counter << endl;     

      for(i = 0; i < populationSize; i++)
      {
        population[i].calcFitness(parameters);
        cout << "Member " << i+1 
             << " L: " << population[i].getLength()
             << " B: " << population[i].getBeam() 
             << " T: " << population[i].getDraft() 
             << " Cb: "<< population[i].getBlockCoeff()
             << " Fitness: ";
        cout.precision(4);
        cout << population[i].getFitness() << endl;
        cout.precision(1);
      }
    }
    else
    {
      for(i = 0; i < populationSize; i++)
      {
        population[i].calcFitness(parameters);
      }
    }
     
    for(i = 0; i < populationSize; i++) // write to text file each gen.
    {
      outFile  << counter << " "
               << population[i].getLength() << " "
               << population[i].getBeam() << " "
               << population[i].getDraft() << " "
               << population[i].getBlockCoeff() << " "
               << population[i].getFitness() << "\n";
       
      if(outFile.fail())
      {
        cout << "ERROR: Unable to write to " << GAoutput << endl
             << "Populations will not be written to file." << endl;
      }         
    }
        
    if(counter < generations)  // Do not select/cross/mutate on the last round
    {
      selectionOp();
      crossoverOp();
      mutationOp();
    }
    if(counter == generations) // Check stopping conditions
    {
      stop = true;
    }

    counter++;
  }

  double bestIndividual = population[0].getFitness(); // fittest member
  int    bestIndex      = 0;                          // track member #

  for(i = 0; i < populationSize; i++)
  {
    if(population[i].getFitness() < bestIndividual)
    {
      bestIndividual = population[i].getFitness();
      bestIndex      = i;
    }
  }
  cout << endl
       << "*****************************************************" << endl
       << "Best Individual is: " << endl
       << "Member " << bestIndex+1
       << " L: " << population[bestIndex].getLength()
       << " B: " << population[bestIndex].getBeam();
  if(parameters.getHulls() == 2)
  {
    cout << " BOA: " << population[bestIndex].getLength()*0.3
                      + population[bestIndex].getBeam();
  }
  cout << " T: " << population[bestIndex].getDraft() 
       << " Cb: "<< population[bestIndex].getBlockCoeff()
       << " Fitness: ";
  cout.precision(4);
  cout << population[bestIndex].getFitness() << endl;
  cout.precision(1);
  cout << "Resistance (Newtons): " << getResistance(
                                 population[bestIndex].getLength(),
                                 population[bestIndex].getBeam(),
                                 population[bestIndex].getDraft(),
                                 population[bestIndex].getBlockCoeff(),
                                 parameters.getVelocity(),
                                 parameters.getHulls()) << endl
       << "Required Power (Horsepower): " << getResistance(
                                 population[bestIndex].getLength(),
                                 population[bestIndex].getBeam(),
                                 population[bestIndex].getDraft(),
                                 population[bestIndex].getBlockCoeff(),
                                 parameters.getVelocity(),
                                 parameters.getHulls())
                                 *0.51444*parameters.getVelocity()
                                 *0.001341*2 << endl;

  outFile.close();
}

//Uses a Roulette Wheel Operator as a selection tool
void GeneticAlgorithmClass::selectionOp()
{
  double popResistance[populationSize];  //resistance of each member of the 
                                         //  population
  double percentTotal[populationSize];   //individual percent of the of the 
                                         //  total resistance 
  double cumulPercent[populationSize];   //cumualative percent of each 
                                         //  individual

  double cumulTotal = 0;                 //total percent
  int    i          = 0;                 //counter integer
  int    j          = 0;                 //counter integer
  double randomPct  = 0;                 //random percentage
  double maxFitness = 0; // used for converting to minimization problem

  for(i = 0; i < populationSize; i++) // determine the worst fitness value
  {
    if(population[i].getFitness() > maxFitness)
    {
      maxFitness = population[i].getFitness();
    }
  }

  for(i = 0; i < populationSize; i++)        // determine the cumulative %'s
  {
    popResistance[i] = population[i].getFitness() - maxFitness;
    cumulTotal +=  popResistance[i];
  }                  

  for(i = 0; i < populationSize; i++) // determine % assigned to each member
  {   
    percentTotal[i] = popResistance[i] / cumulTotal;
    if( i == 0)
    {
      cumulPercent[i] = percentTotal[i];
    }
    else
    {
      cumulPercent[i] = percentTotal[i]+ cumulPercent[i-1];
    }
  }      

  // Used to store chromosomes that are selected for next generation
  ChromosomeClass *TempPopulation;
  TempPopulation = new ChromosomeClass[populationSize];

  for(i = 0; i < populationSize; i++)  // perform Roulette Wheel Selection
  { 
    randomPct = getRand();
    j = 0;

    while(j < populationSize - 1 && randomPct > cumulPercent[j])
    {
      j++;
    }
    
    TempPopulation[i] = population[j];
  }    
 
  for(i = 0; i < populationSize; i++)
  {
    population[i] = TempPopulation[i]; // Assign selected chromosomes
  } 
 
  delete TempPopulation; // Free dynamically allocated memory
}

void GeneticAlgorithmClass::crossoverOp()
{
  int i      = 0;      // loop variables
  int j      = 0;
  int swapTo = 0;      // choose which chromosome in pop. to swap with

  for(i = 0; i < populationSize; i++)
  {
    swapTo = chooseInt(0, populationSize - 1);

    while(swapTo == i) // make sure it doesnt swap with itself
    {
      swapTo = chooseInt(0, populationSize - 1);
    }

    ChromosomeClass temp  = population[swapTo];
    population[swapTo]    = population[i];
    population[i]         = temp;
  }
  
  double numToCrossover = populationSize * crossoverPct;
  numToCrossover        = floor(numToCrossover / 2.0);// 2 parents => 1 cross
  
  for(i = 0; i < numToCrossover; i++)
  {
    population[2*i].crossover(population[2*i+1]);
  }

}

void GeneticAlgorithmClass::mutationOp()
{
  int    geneToMutate = chooseInt(0,3); // Choose gene 1 thru 4
  int    i            = 0;                     
  double mutateRand   = 0;

  for(i = 0; i < populationSize; i++)
  {
    mutateRand = getRand();

    if(mutateRand <= mutationPct)
    {
      geneToMutate = chooseInt(0,NUM_GENES);
      population[i].mutate(geneToMutate); // Mutate correct gene in chromosome
    }
  }
}


