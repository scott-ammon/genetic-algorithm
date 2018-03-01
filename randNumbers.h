// *************************************************************************//
// This code creates random numbers for use with the genetic algorithm
// *************************************************************************//

#ifndef _RANDNUMBERS_H_
#define _RANDNUMBERS_H_

// Sets the seed value for the random number algorithm srand()
void setSeed(int seedVal);

// Returns a uniformly distributed random number between min and max
int chooseInt(int min, int max);

// Returns a double value between the minimum and maximum
double chooseDouble(double min, double max);

// Returns a random number between 0 and 1
double getRand();

// Returns a normally distributed random number given mean, std. deviation
int getNormal(float mean, float stdDev);

#endif
