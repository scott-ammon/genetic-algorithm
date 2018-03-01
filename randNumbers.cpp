// ********************* Random Numbers Source Code ************************//

#include <iostream>
using namespace std;

void setSeed(int seedVal)
{
  srand(seedVal);
}

int chooseInt(int min,int max)
{
  int uniRand;
  uniRand = rand() % ((max + 1) - min) + min;
  return (uniRand);
}

double chooseDouble(double min,double max)
{
  double RandD;
  RandD = min + ((max - min) * rand())/ (RAND_MAX + 1.0);
  return (RandD);
}

double getRand()
{
  return rand() / double(RAND_MAX); 
}

int getNormal(float mean,float stdDev)
{
  const int NUM_UNIFORM = 12;
  const int MAX = 1000;
  const float ORIGINAL_MEAN = NUM_UNIFORM * 0.5;
  float sum;
  int i;
  float standardNormal;
  float newNormal;
  int uni;

  sum = 0;
  
  for (i = 0; i < NUM_UNIFORM; i++)
  {
    uni = rand() % (MAX + 1);
    sum += uni;
  }
  
  sum = sum / MAX;
  standardNormal = sum - ORIGINAL_MEAN;
  newNormal = mean + stdDev * standardNormal;

  if (newNormal < 0)
  {
    newNormal *= -1;
  }
  return ((int)newNormal);
}

