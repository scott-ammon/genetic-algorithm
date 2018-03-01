#include "ChromosomeClass.h"
#include "GeneClass.h"
#include "GlobalConstants.h"
#include "resistanceFunction.h"
#include "ParameterClass.h"

#include <iostream>  
#include <cmath>  

using namespace std;  

/*******************************************************************************
  Class conatains all of the information and functionality for the chromosomes 
    of the genetic algorithm.
*******************************************************************************/
   
//Default constructor; intializes everything to zero.      
ChromosomeClass::ChromosomeClass()
{
  chromosome[LENGTH_INDEX].setValue(0.0);
  chromosome[BEAM_INDEX].setValue(0.0);
  chromosome[DRAFT_INDEX].setValue(0.0);
  chromosome[BLOCK_COEFF_INDEX].setValue(0.0);
  
  fitness = 0.0;    
}

//Copy constructor; takes in an array of values, lower bounds, and upper bounds  
//  and assigns them to their corresponding chromosome
ChromosomeClass::ChromosomeClass(double *value,double *loBound,double *upBound)
{
  //sets each gene in the chromosome array
  for(int i = 0; i < NUM_GENES; i++)
  {
    chromosome[i].setGene(value[i], loBound[i], upBound[i]);
  } 
   
  fitness    = 0.0;
}  
   
//Takes in an array of values, lower bounds, and upper bounds and assigns them 
//  to their corresponding chromosome
void ChromosomeClass::setChromosome(double *value,double *loBound, 
                                                  double *upBound)
{
  for(int i = 0; i < NUM_GENES; i++)
  {
    chromosome[i].setGene(value[i], loBound[i], upBound[i]);
  }  
}

//Takes in an array of genes and assigns each one to the chromosome array
void ChromosomeClass::setChromosome(GeneClass< double > *gene)
{
  for(int i = 0; i < NUM_GENES; i++)
  {
    chromosome[i].setValue(gene[i].getValue());
    chromosome[i].setLoBound(gene[i].getLoBound());
    chromosome[i].setUpBound(gene[i].getUpBound());
  }  
}    

//returns the value of the length chromosome
double ChromosomeClass::getLength() 
{
  return(chromosome[LENGTH_INDEX].getValue());
}

//returns the value of the beam chromosome
double ChromosomeClass::getBeam() 
{
  return(chromosome[BEAM_INDEX].getValue());
}  

//returns the value of the draft chromosome
double ChromosomeClass::getDraft() 
{
  return(chromosome[DRAFT_INDEX].getValue());
}  

//returns the value of the block coefficient chromosome
double ChromosomeClass::getBlockCoeff() 
{
  return(chromosome[BLOCK_COEFF_INDEX].getValue());
}  

//returns the gene at the specified index
GeneClass< double > ChromosomeClass::getGene(int geneIndex)
{
  return(chromosome[geneIndex]);
}  

//"Crosses over" the current chromosome and another chromosome's gene at the 
//  specified gene; induces search properties of the GA
//All equations from "Multi-Objective Optimization using Evolutionary
//  Algorithms"
//  K. Deb (2001)
void ChromosomeClass::crossover(ChromosomeClass &parentTwo)
{
  int geneIndex;                                   //index of gene being crossed 
                                                   //  over
  GeneClass< double > geneOffspringOne[NUM_GENES]; //first offspring gene class 
                                                   //  array
  GeneClass< double > geneOffspringTwo[NUM_GENES]; //second offsrping gene class 
                                                   //  arrary
  GeneClass< double > *output;                     //array of gene class objects

  output = new GeneClass< double >[NUM_OFFSPRING];             

  //cross over each gene and set the output to the geneOffspring objects
  for( geneIndex = 0; geneIndex < NUM_GENES; geneIndex++ )
  {
    output = chromosome[geneIndex].crossoverGene(parentTwo.getGene(geneIndex));
    geneOffspringOne[geneIndex] = output[0];       
    geneOffspringTwo[geneIndex] = output[1];           
  }  
    
  //set current chromosome to offspring one
  setChromosome(geneOffspringOne);  
  //set parent to the the second offspring array
  parentTwo.setChromosome(geneOffspringTwo);     
}


//"Mutates" the specified gene; induces search properties of the GA
//All equations from "Multi-Objective Optimization using Evolutionary 
//  Algorithms"
//  K. Deb (2001)
void ChromosomeClass::mutate(int geneIndex)
{
  GeneClass< double > mutatedGene;         //gene that is mutated
  
  //uses the mutateGene() function in the gene class to mutate the gene 
  //  specified 
  mutatedGene = chromosome[geneIndex].mutateGene();
  
  //set the chromosome at the specified index to the mutated gene
  chromosome[geneIndex] = mutatedGene;
}

//Same functionality as the previous "mutate()" function, but takes in an array 
//  of gene indices and mutates several genes at once
void ChromosomeClass::mutate(int *geneIndex)
{
  int numOfIndices;           //total number indices in array
  
  //find the number of genes to mutate
  numOfIndices = sizeof(geneIndex)/sizeof(*geneIndex);

  //mutate each gene using the GeneClass function mutateGene()
  for(int i = 0; i < numOfIndices; i++)
  {
    chromosome[geneIndex[i]] = chromosome[geneIndex[i]].mutateGene(); 
  }  
}  

//returns the fitness of the chromosome
double ChromosomeClass::getFitness() const
{
  return(fitness);
}  

//calculates the fitness of the current chromosome
void ChromosomeClass::calcFitness(ParameterClass &parameters)
{
	//uses the global resistance function and the parameters to get the fitness
	//  function of the current chromosome
  double resistance = getResistance(chromosome[LENGTH_INDEX].getValue(), 
                                    chromosome[BEAM_INDEX].getValue(), 
                                    chromosome[DRAFT_INDEX].getValue(), 
                                    chromosome[BLOCK_COEFF_INDEX].getValue(), 
                                    parameters.getVelocity(),
                                    parameters.getHulls());
  
  //maximum resistance of the chromosome                                  
  double maxResistance = parameters.getMaxResistance();
   
  //calculates the hull separation for a catamaran 
  double separation = chromosome[LENGTH_INDEX].getValue() * 
                      CAT_SEPARATION_CONST;
  
  //normalizes the resistance
  double resistanceFitness = resistance/maxResistance;

  //sets the fitness to 1 if the resistance is less than 0 
  if(resistance<=0)
  {
    resistanceFitness = 1;
  }
	//calculates the total weight of the ship and the displacement of the ship 
	//  represented by the current chromosome
  double weight = parameters.getCars() * AVG_CAR_WEIGHT * WEIGHT_CONSTANT;
  double displacement = chromosome[LENGTH_INDEX].getValue() *
                        chromosome[BEAM_INDEX].getValue() *
                        chromosome[DRAFT_INDEX].getValue() *
                        chromosome[BLOCK_COEFF_INDEX].getValue()*
                        DENSITY;
  
  //if the hull is a catamaran hull, the displacement is twice the displacement
  //  of one hull
  if(parameters.getHulls() == CATAMARAN_OPT)
  {
    displacement = displacement * double(CATAMARAN_OPT);
  }

  double weightPenalty = 0;
  double shapePenalty = 0;

  //sets penalties based on the physical limitations of the ship
  //  the limitations are based on regressions or physics  
  //Penalties set based on standard equations
  
  //weight = displacement within 5%
  if (abs(weight-displacement)>(WEIGHT_DISPL_DIFF * displacement))
  {
    weightPenalty = 10 * abs(weight-displacement)/displacement;
  }
  
  //L/B >  4
  if (chromosome[LENGTH_INDEX].getValue()/chromosome[BEAM_INDEX].getValue() < 
                                                                        MIN_L_B)
  {
    shapePenalty = 4 - (chromosome[LENGTH_INDEX].getValue() / 
                      chromosome[BEAM_INDEX].getValue());
  }
  if (parameters.getHulls() == MONOHULL_OPT)
  {  
    //L/B < 12
    if (chromosome[LENGTH_INDEX].getValue()/chromosome[BEAM_INDEX].getValue() > 
                                                                        MAX_L_B)
    {
      shapePenalty = (chromosome[LENGTH_INDEX].getValue() / 
                      chromosome[BEAM_INDEX].getValue())/12;
    }
  }

  // 2 < B/T < 4
  if (chromosome[BEAM_INDEX].getValue()/chromosome[DRAFT_INDEX].getValue() > 
                                                                        MAX_B_T)
  {
    shapePenalty = shapePenalty+(chromosome[BEAM_INDEX].getValue()/
                   chromosome[DRAFT_INDEX].getValue())/4;
  }  
  if (chromosome[BEAM_INDEX].getValue()/chromosome[DRAFT_INDEX].getValue() < 
                                                                        MIN_B_T)
  {
    shapePenalty = shapePenalty+2/(chromosome[BEAM_INDEX].getValue()/
                   chromosome[DRAFT_INDEX].getValue())-0.5;
  }
  
  //for catamarans
  if (parameters.getHulls() == CATAMARAN_OPT)
  {
    // 10 < L/B < 20
    if (chromosome[LENGTH_INDEX].getValue() / chromosome[BEAM_INDEX].getValue()
                                                                  < CAT_MIN_L_B) 
    {
      shapePenalty = shapePenalty + 10 / (chromosome[LENGTH_INDEX].getValue() /
                     chromosome[BEAM_INDEX].getValue());
    }
    if (chromosome[LENGTH_INDEX].getValue() / chromosome[BEAM_INDEX].getValue()
                                                                  > CAT_MAX_L_B) 
    {
      shapePenalty = shapePenalty + (chromosome[LENGTH_INDEX].getValue() /
                     chromosome[BEAM_INDEX].getValue()) / 20;
    }
  }
  
  //the fitness function is the ship's resistance + the penalties
  fitness = resistanceFitness+weightPenalty+shapePenalty;

}  
