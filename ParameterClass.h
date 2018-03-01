#ifndef _PARAMETERCLASS_H_
#define _PARAMETERCLASS_H_

// PARAMETER CLASS
// This class computes the ranges for the vessel characteristics
// that are feasible in terms of the resistance prediction method,
// and consists of getter and setter functions to allow them 
// to be accessed in the Genetic Algorithm class

class ParameterClass
{
  private:
    double velocity;  // ship's speed in meters/second
    double minLength; // minimum and maximum ranges for vessel dimensions
    double maxLength;
    double minBeam;
    double maxBeam;
    double minDraft;
    double maxDraft;
    int    numberCars;   // number of cars the ferry will carry
    int    numberHulls;  // either 1 for monohull, or 2 for catamaran

  public:
    // Constructor takes ship speed, number of cars, and ship type as inputs
    ParameterClass(double speed,int cars,int hulls);
    
    // Getter functions for the member variables
    double getMaxResistance();
    double getMaxLength();
    double getMinLength();
    double getMaxBeam();
    double getMinBeam();
    double getMaxDraft();
    double getMinDraft();
    double getVelocity();
    int    getCars();
    int    getHulls();

};
#endif
