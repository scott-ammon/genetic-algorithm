#ifndef _GENECLASS_H_
#define _GENECLASS_H_

using namespace std;

/*******************************************************************************

Class that contains all of the information in the genes that make up the
  chromosome class. It is a templated class so the chromosomes can contain
  anything.

*******************************************************************************/

template < class T >
class GeneClass
{
  private:
    T geneValue;  //value of the gene at 
    T loBound;    //lower bound on the value of the gene
    T upBound;    //upper bound on the value of the gene
		
  public:
    GeneClass();
    GeneClass(T value, T inLoBound, T inUpBound);
    GeneClass(T &value, T &inLoBound, T &inUpBound);
  	
    void setGene(T value, T inLoBound, T inUpBound);
    void setGene(T *value, T *inLoBound, T *inUpBound);
    void setValue(T val);
    void setLoBound(T inLoBound);
    void setUpBound(T inUpBound);
  	
    T getLoBound();
    T getUpBound();
    T getValue();
  	
    GeneClass< T >* crossoverGene(GeneClass< T > parentTwo);
    GeneClass< T > mutateGene();  	
};

#include "GeneClass.inl"

#endif
