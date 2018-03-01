#include <iostream>
using namespace std;
#include <cmath>

#include "ParameterClass.h"
#include "resistanceFunction.h"
#include "GlobalConstants.h"

ParameterClass::ParameterClass(double speed,int cars,int hulls)
{
  velocity = speed;
  numberCars = cars;
  numberHulls = hulls;
  
  // Based on input ranges for Series 64 Resistance Prediction Method
  minLength = pow(velocity*0.51444,2)/9.81;
  maxLength = pow(velocity*0.51444,2)/1.57;

  minDraft = pow(velocity*0.51444,2)/567.45;
  maxDraft = pow(velocity*0.51444,2)/29.72;

  minBeam = 2*minDraft;
  maxBeam = 4*maxDraft;
}

double ParameterClass::getMaxResistance()
{
  return (getResistance(maxLength,maxBeam,maxDraft,MAX_BLOCK_COEFF,
                                              velocity,numberHulls));
}

double ParameterClass::getMaxLength()
{
  return (maxLength);
}

double ParameterClass::getMinLength()
{
  return (minLength);
}

double ParameterClass::getMaxBeam()
{
  return (maxBeam);
}

double ParameterClass::getMinBeam()
{
  return (minBeam);
}

double ParameterClass::getMaxDraft()
{
  return (maxDraft);
}

double ParameterClass::getMinDraft()
{
  return (minDraft);
}

double ParameterClass::getVelocity()
{
  return (velocity);
}

int ParameterClass::getCars()
{
  return (numberCars);
}

int ParameterClass::getHulls()
{
  return (numberHulls);
}


