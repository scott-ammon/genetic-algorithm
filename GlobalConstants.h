#ifndef _GLOBALCONSTANTS_H_
#define _GLOBALCONSTANTS_H_

/******************************************************************************* 
 This file contains all of the global constants used in this project
*******************************************************************************/

const int MAX_POPULATION   = 1000;     //maximum popluation size
const int MAX_GENERATIONS  = 1000;     //maximum generation size
const double MAX_MUTATION  = 0.10;     //maximum mutation percentage
const double MAX_CROSSOVER = 1;        //maximum crossover percentage
const int MAX_CARS         = 500;      //maximum number of cars
const int MIN_CARS         = 25;       //minimum number of cars

const int MAX_SPEED        = 60;      //maximum allowable speed

const int MONOHULL_OPT  = 1;          //Number of hulls for a monohull
const int CATAMARAN_OPT = 2;          //Number of hulls for a catamaran

const int SEED = 35;                  //seed for the random number generator

const int NUM_GENES    = 4;           //total number of genes in the chromosome
const int LENGTH_INDEX = 0;           //the index in the chromosome of the 
                                      //  length gene
const int BEAM_INDEX   = 1;           //the index in the chromosome of the beam
                                      //  gene
const int DRAFT_INDEX  = 2;           //the index in the chromosome of the draft
                                      //  gene
const int BLOCK_COEFF_INDEX = 3;      //the index in the chromosome of the block
                                      //  coefficient gene

const int ETA = 2;                    //user defined exponential parameter

const double MODEL_LENGTH = 3.05;

const double GRAVITY = 9.81;          //acceleration of gravity in m/sec^2

const double MIN_BLOCK_COEFF = 0.35;  //minimum block coefficient allowed
const double MAX_BLOCK_COEFF = 0.55;  //maximum block coefficient allowed

const double DENSITY = 1.025;         //density of water in tons/m^3

const double AVG_CAR_WEIGHT = 1.8;    //average weight of a car

const double WEIGHT_CONSTANT = 3;     //

const double CAT_SEPARATION_CONST = 0.3; //constant used to find catamaran hull
                                         //  separation

const int NUM_OFFSPRING = 2;           //Number of offspring in the crossover 
                                       //  operator

const double WEIGHT_DISPL_DIFF = 0.05; //Maximum allowable percent difference  
                                       // between weight and displacement

const int MIN_L_B = 4;                 //Minimum Length/Beam ratio allowed
const int MAX_L_B = 12;                //Maximum Length/Beam ratio allowed
const int MAX_B_T = 4;                 //Maximum Beam/Draft ratio allowed
const int MIN_B_T = 2;                 //Minimum Beam/Draft ratio allowed
const int CAT_MIN_L_B = 10;            //Minimum Length/Beam ratio allowed for
                                       //  catamarans
const int CAT_MAX_L_B = 20;            //Maximum Length/Beam ratio allowed for
                                       //  catamarans


#endif
