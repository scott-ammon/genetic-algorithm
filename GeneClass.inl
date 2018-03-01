#include <iostream>
#include <cmath>

#include "GeneClass.h"
#include "randNumbers.h"
#include "GlobalConstants.h"

using namespace std;

//Default constructor; initializes everything to zero
template < class T >
GeneClass< T >::GeneClass()
{
  geneValue = 0;
  loBound   = 0;
  upBound   = 0;
}

//Copy constructor; initializes the gene to values passed in to the user
template < class T >
GeneClass< T >::GeneClass(T value, T inLoBound, T inUpBound)
{
  geneValue = value;
  loBound   = inLoBound;
  upBound   = inUpBound;
}

//Copy constructor; initializes the gene to values passed in to the user
template < class T > 
GeneClass< T >::GeneClass(T &value, T &inLoBound, T &inUpBound)
{
  geneValue = *value;
  loBound   = *inLoBound;
  upBound   = *inUpBound;
}  

//Sets the gene's values to the values passed in by the user 
template < class T >
void GeneClass< T >::setGene(T value, T inLoBound, T inUpBound)
{
  geneValue = value;
  loBound = inLoBound;
  upBound = inUpBound;
}  

//Sets the gene's values to the values passed in by the user 
template < class T >
void GeneClass< T >::setGene(T *value, T *inLoBound, T *inUpBound)
{
  geneValue = *value;
  loBound   = *inLoBound;
  upBound   = *inUpBound; 
}   	 

//sets the value to the value passed in 
template < class T >  
void GeneClass< T >::setValue(T val)
{
  geneValue = val;
}

//sets the lower bound to the value passed in 
template < class T >
void GeneClass< T >::setLoBound(T inLoBound)
{
  loBound = inLoBound;
}

//sets the upper bound to the value passed in
template < class T >
void GeneClass< T >::setUpBound(T inUpBound)
{
  upBound = inUpBound;
}

//returns the lower bound
template < class T >
T GeneClass< T >::getLoBound()
{
  return(loBound);
}

//returns the upper bound
template < class T >
T GeneClass< T >::getUpBound()
{
  return(upBound);
}

//returns the value of the gene
template < class T >
T GeneClass< T >::getValue()
{
  return(geneValue);
}    

//crosses over the gene; Passes in the gene from parentTwo and returns an array 
//  of two gene class objects that correspond to the new offspring
//All equations from 'Multi-Objective Optimization using Evolutionary 
//  Algorithms' K. Deb (2001)
template < class T >
GeneClass< T >* GeneClass< T >::crossoverGene(GeneClass< T > parentTwo)
{
  double uVal;               //random probability used to compute beta; has 
                             //  domain of [0,1]
  double beta;               //represents "amount" of gene the offspring will 
                             //  receive from each parent
  GeneClass *offspring;      //new offspring found from calculations  
  
  offspring = new GeneClass< T >[NUM_OFFSPRING];
  
  //sets the value of uVal
  uVal = getRand();
  
  //beta is set according to the value of uVal; based upon probability
  if( uVal <= 0.5 )
  {
    beta = pow((2.0 * uVal), (1.0 / (ETA + 1)));
  }
  else
  {
    beta = pow((1.0 / (2.0 * (1.0 - uVal))), (1.0 / (ETA + 1)));
  }
  
  //calculates first offspring
  offspring[0].setValue( 0.5 * ((1.0 + beta ) * geneValue + 
                 (1.0 - beta) * parentTwo.getValue()) );
               
  //cacluates second offspring
  offspring[1].setValue( 0.5 * ((1.0 - beta ) * geneValue + 
                 (1.0 + beta) * parentTwo.getValue()) );
  
  //if offspring one is set below the lower bound or above the upper bound, the
  // gene value is set to the respective bound of the gene                
  if( offspring[0].getValue() < loBound )
  {
    offspring[0].setValue(loBound);
  }
  else if( offspring[0].getValue() > upBound)
  {
    offspring[0].setValue(upBound);
  }
  
  //if offspring two is set below the lower bound or above the upper bound, the
  // gene value is set to the respective bound of the gene     
  if( offspring[1].getValue() < loBound )
  {
    offspring[1].setValue(loBound);
  }
  else if( offspring[1].getValue() > upBound)
  {
    offspring[1].setValue(upBound);
  }                 

  //sets the lower and upper bound of the two genes
  offspring[0].setLoBound(loBound);
  offspring[0].setUpBound(upBound);
  offspring[1].setLoBound(loBound);
  offspring[1].setUpBound(upBound);
  
  return(offspring); 
}  

//Mutates the current gene; returns a new gene class object
//All equations from 'Multi-Objective Optimization using Evolutionary 
//  Algorithms' K. Deb (2001)
template < class T >
GeneClass< T > GeneClass< T >::mutateGene()
{
  GeneClass< T > mutatedGene;         //mutated gene to be created
  T mutatedGeneValue;                 //value of the mutated gene
  double rVal;                        //random number in the interval [0,1]
  double delta;                       //"amount" the gene will be mutated

  //gets the rVal
  rVal = getRand();

  //sets delta based on probablity chosen by rVal
  if( rVal < 0.5 )
  {
    delta = pow((2.0 * rVal), (1.0/(ETA + 1.0))) - 1.0;
  }
  else
  {
    delta = 1.0 - pow((2.0 * (1.0 - rVal)), (1/(ETA + 1.0)));
  }
  
  //sets the mutated gene's value based on the current value, the delta value, 
  //  and the greatest range of values possible
  mutatedGeneValue = geneValue + (upBound - loBound) * delta;

  //if the gene's value is less than the lower bound, the gene is set to the 
  //  lower bound
  if( mutatedGeneValue < loBound )
  {
    mutatedGeneValue = loBound;
  }
  //if the gene's value is greater than the upper bound, the gene is set to the
  //   upper bound
  else if( mutatedGeneValue > upBound)
  {
    mutatedGeneValue = upBound;
  }    
    
  //sest the current gene to the mutated gene's value, the lower bound, and the 
  // upper bound
  mutatedGene.setGene(mutatedGeneValue, loBound, upBound);    
                
  return(mutatedGene);  
}  
