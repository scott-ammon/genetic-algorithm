#include <iostream>
#include <exception>
using namespace std;

#include "randNumbers.h"
#include "GeneticAlgorithmClass.h"
#include "ParameterClass.h"

int main(void)
{
  //header to output to the screen
  cout << "****************************************************" << endl
       << "G.A. Optimization of Hull Parameters for Car Ferry"   << endl
       << "****************************************************" << endl
       << endl
       << "This program takes in a required number of vehicles," << endl
       << "and required speed. An optimization is performed to"  << endl
       << "determine the best Length, Beam, Draft, and Block"    << endl
       << "Coefficient that satisfy the constraints, while"      << endl
       << "achieving minimum resistance."                        << endl;

  int    cars     = 0;                 //number of cars set by user
  double speed    = 0;                 //speed set by user
  double minSpeed = 0;                 //minimum and maximum speed determined by 
                                       //  the number of cars selected
  double maxSpeed = 0;
  int    hulls    = 0;                 //number of hulls - one or two
  
  cout.unsetf(ios::floatfield);        // set precision for output of speeds
  cout.setf(ios::showpoint);
  cout.precision(3);
  
  //user menu
  cout << endl << "VESSEL CHARACTERISTICS" << endl
       << "Choose (1) Monohull, or (2) Catamaran: ";
  cin  >> hulls;       
  //checks user input
  while(cin.fail() || hulls != 1 && hulls != 2)
  {
    cin.clear();
    cin.ignore(200, '\n');
    cout << "ERROR! Invalid input." << endl;
    cout << "Choose (1) Monohull, or (2) Catamaran: ";
    cin  >> hulls;
  }  

  cout << "Enter the number of cars required: ";
  cin  >> cars;  
  //checks user input
  while(cin.fail() || cars < MIN_CARS || cars > MAX_CARS)
  {
    cin.clear();
    cin.ignore(200, '\n');
    cout << "ERROR! Invalid number of cars." << endl;
    cout << "Enter the number of cars required: ";
         cin  >> cars;
  }  

  // Regression to determine velocity range, coefficients used
  minSpeed = pow(630.34*cars*AVG_CAR_WEIGHT*WEIGHT_CONSTANT,1.0/6.0)/0.5144;
  maxSpeed = pow(4512593.03*cars*AVG_CAR_WEIGHT*WEIGHT_CONSTANT,1.0/6.0)/0.5144;


  //if the maximum speed is greater than the maximum allowable speed, set the 
  //  maximum speed to the maximum allowable speed
  if(maxSpeed > MAX_SPEED)
  {
    maxSpeed = MAX_SPEED;
  }  

  cout << "Enter the desired speed, in the range: " << minSpeed
       << " to " << maxSpeed << " (knots): ";
  cin  >> speed;
  //checks user input
  while(cin.fail() || speed < minSpeed || speed > maxSpeed)
  {
    cin.clear();
    cin.ignore(200, '\n');
    cout << "ERROR: Invalid speed entered." << endl;
    cout << "Enter the desired speed, in the range: " << minSpeed
       << " to " << maxSpeed << " (knots): ";
    cin  >> speed;
  }  
  
  
  double mutationPct    = 0;
  double crossoverPct   = 0;
  int    generations    = 0;
  int    populationSize = 0;
  int    defaultChoice  = 0;

  cout << endl << "GENETIC ALGORITHM PARAMETERS" << endl
       << "Input population size: ";
  cin  >> populationSize;
  //checks user input
  while(cin.fail())
  {
    cin.clear();
    cin.ignore(200, '\n');
    cout << "ERROR: Invalid type entered for population size." << endl;
    cout << "Input population size: ";
    cin  >> populationSize;
  }
    
  cout << "Input number of generations: ";
  cin  >> generations;
  //checks user input
  while(cin.fail())
  {
    cin.clear();
    cin.ignore(200, '\n');  
    cout << "ERROR: Invalid type entered for generation size." << endl;
    cout << "Input number of generations: ";
    cin  >> generations;
  }
  
  cout << "Crossover, Mutation Percentages: " << endl
       << "1. Use Defaults (C-80%, M-0.1%) "  << endl 
       << "2. Choose percentages"             << endl
       << "Your Choice: ";
  cin  >> defaultChoice;
  while(cin.fail() || defaultChoice < 1 || defaultChoice > 2)
  {
    cin.clear();
    cin.ignore(200, '\n');  
    cout << "ERROR: Invalid menu choice." << endl;
    cout << "Your choice: ";
    cin  >> defaultChoice;
  }

  if(defaultChoice == 2)
  {
    cout << "Input Crossover Percent (0 to 1): ";
    cin  >> crossoverPct;
    //checks user input
    while(cin.fail())
    {
      cin.clear();
      cin.ignore(200, '\n');  
      cout << "ERROR: Invalid type entered for crossover percent." << endl;
      cout << "Input Crossover Percent (0 to 1): ";
      cin  >> crossoverPct;
    }
  
    cout << "Input Mutation Percent (0 to 0.1): ";
    cin  >> mutationPct;
    //checks user input
    while(cin.fail())
    {
      cin.clear();
      cin.ignore(200, '\n');
      cout << "ERROR: Invalid type entered for Mutation Percent." << endl;
      cout << "Input Mutation Percent (0 to 0.1): ";
      cin  >> mutationPct;
    }
  }   
  else
  {
    crossoverPct = 0.8;  // Default values
    mutationPct  = 0.002;
  }  
  GeneticAlgorithmClass GA;
  GA.setMutation(mutationPct);
  GA.setCrossover(crossoverPct);
  GA.setGenerations(generations);

  ParameterClass param(speed,cars,hulls);
  GA.initializePopulation(populationSize,param);

  setSeed(0);
  int i;

  GA.runGeneticAlgorithm(param);
  cout << "Feasible Variable Ranges Tested:" << endl
       << "Length Range (m): " << param.getMinLength() << " " 
                               << param.getMaxLength() << endl 
       << "Beam Range   (m): " << param.getMinBeam() << " " 
                               << param.getMaxBeam() << endl
       << "Draft Range  (m): " << param.getMinDraft() << " " 
                               << param.getMaxDraft() << endl;
  return(0);
}






