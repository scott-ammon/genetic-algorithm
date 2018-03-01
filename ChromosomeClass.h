#ifndef _ChromosomeClass_H_
#define _ChromosomeClass_H_

#include "GeneClass.h"
#include "GlobalConstants.h"
#include "ParameterClass.h"
#include "resistanceFunction.h"

using namespace std;

class ChromosomeClass
{
  private:
    //array containing all of the genes for the ship; the genes represent the 
    //  length, beam, draft, and block coefficient, respectively                                
    GeneClass< double > chromosome[NUM_GENES]; 
                                  
    double fitness;          //calculates resistance using objective function           
    
  public:
    ChromosomeClass();
    ChromosomeClass(double *value, double *loBound, double *upBound);
    
    void setChromosome(double *value,double *loBound,double *upBound);
    void setChromosome(GeneClass< double > *gene);
        
    double getLength();
    double getBeam();
    double getDraft();
    double getBlockCoeff();
    GeneClass< double > getGene(int geneIndex);
    
    void crossover(ChromosomeClass &parentTwo); 
    void mutate(int geneIndex);
    void mutate(int *geneIndex);    
    void calcFitness(ParameterClass &parameters);
    
    double getFitness() const;  
};    

#endif    
    
