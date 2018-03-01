
#include <iostream>
#include <cmath>
using namespace std;
#include "GlobalConstants.h"


//Uses series 64 model test data for high speed hulls to estimate the 
//resistance of the ship
double getResistance(double length, double beam, double draft, double Cb,
                     double velocity_knots, int hulls)
{
  double resistance = 0;
  double velocity = velocity_knots*0.5144;
  double Fn = velocity/sqrt(GRAVITY*length);
  double Re = length*velocity/(0.000001906);
  double hullVolume = length*beam*draft*Cb;
  double dim_length = 0;
  double overallBeam = 0; 

  if (hulls == 2)
  {
    hullVolume = 2*hullVolume;
    dim_length = length/pow(hullVolume/2,1.0/3.0);
  }
  else
  {
    dim_length = length/pow(hullVolume,1.0/3.0);
  }

  double Cr = 0;
  double modelSpeed = Fn*sqrt(GRAVITY*MODEL_LENGTH);
  double ReModel = MODEL_LENGTH*modelSpeed/(0.000001906);
  double formFactor = 0;
  double frictCoeffShip = 0.075/pow(log10(Re)-2,2);
  double frictCoeffModel = 0.075/pow(log10(ReModel)-2,2);
  double ratioBtoT = beam/draft;
  double totalCoeff = 0;
  double hullResistance = 0;
  double surfaceCoeff = 6.554-1.226*ratioBtoT+0.216*pow(ratioBtoT,2)-15.409*Cb+
                        4.468*Cb*ratioBtoT-0.694*pow(ratioBtoT,2)*Cb+15.404*pow
                        (Cb,2)-4.527*pow(Cb,2)*ratioBtoT+0.655*pow(ratioBtoT,2)
                        *pow(Cb,2);
  double surfaceArea = surfaceCoeff*sqrt(length*length*beam*draft*Cb);
  double separation = 0;
  double nonDimSep = 0;
  double tr = 0;
  
  if (hulls == 2)
  {
    separation = length*0.3;
    nonDimSep = separation/length;
  }

  if (hulls == 2)
  {
    formFactor = 3.03*pow(dim_length,-0.4);
  }
  else
  {
    formFactor = 2.76*pow(dim_length,-0.4);
  }

  //An array used to calculate a vector which is used to calculate a 
  //coefficient of residuary resistance
  double Cr_Cb_Array[7][3] = {{0.288*pow(dim_length,-2.33),36.726*pow(dim_length
                              ,-4.41),0.926*pow(dim_length,-2.74)},
                              {0.751*pow(dim_length,-2.76),55.159*pow(dim_length
                              ,-4.61),1.775*pow(dim_length,-3.05)},
                              {0.758*pow(dim_length,-2.81),42.184*pow(dim_length
                              ,-4.56),1.642*pow(dim_length,-3.08)},
                              {0.279*pow(dim_length,-2.42),29.257*pow(dim_length
                              ,-4.47),1.106*pow(dim_length,-2.98)},
                              {0.106*pow(dim_length,-2.06),27.130*pow(dim_length
                              ,-4.51),0.783*pow(dim_length,-2.90)},
                              {0.047*pow(dim_length,-1.74),20.657*pow(dim_length
                              ,-4.46),0.458*pow(dim_length,-2.73)},
                              {0.025*pow(dim_length,-1.50),11.644*pow(dim_length
                              ,-4.24),0.199*pow(dim_length,-2.38)},
                             };

  double Cr_Fn_Array[7];

  for (int i=0;i<7;i++)
  {
    Cr_Fn_Array[i] = ((Cb-0.45)*(Cb-0.55)*Cr_Cb_Array[i][0]/0.02)-((Cb-0.35)*(Cb
                     -0.55)*Cr_Cb_Array[i][1]/0.01)+((Cb-0.35)*(Cb-0.45)*
                     Cr_Cb_Array[i][2]/0.02);
  }

  //calculates the residuary resistance
  if (Fn<0.4)
    Cr = 20;
  else if (Fn<0.5)
    Cr = Cr_Fn_Array[0]+((Fn-0.4)*(Cr_Fn_Array[1]-Cr_Fn_Array[0])/0.1);
  else if (Fn<0.6)
    Cr = Cr_Fn_Array[1]+((Fn-0.5)*(Cr_Fn_Array[2]-Cr_Fn_Array[1])/0.1);
  else if (Fn<0.7)
    Cr = Cr_Fn_Array[2]+((Fn-0.6)*(Cr_Fn_Array[3]-Cr_Fn_Array[2])/0.1);
  else if (Fn<0.8)
    Cr = Cr_Fn_Array[3]+((Fn-0.7)*(Cr_Fn_Array[4]-Cr_Fn_Array[3])/0.1);
  else if (Fn<0.9)
    Cr = Cr_Fn_Array[4]+((Fn-0.8)*(Cr_Fn_Array[5]-Cr_Fn_Array[4])/0.1);
  else if (Fn<1.0)
    Cr = Cr_Fn_Array[5]+((Fn-0.9)*(Cr_Fn_Array[6]-Cr_Fn_Array[5])/0.1);
  else 
    Cr = 20;

  //An array used for calculating wave interference between the two hulls
  double hullInterference[7][4] = {{1.862*pow(dim_length,-0.15),0.941*pow(
                                   dim_length,0.7),0.73*pow(dim_length,0.28),
                                   0.645*pow(dim_length,0.32)},
                                   {1.489*pow(dim_length,0.04),1.598*pow(
                                   dim_length,-0.05),0.856*pow(dim_length,0.2),
                                   0.485*pow(dim_length,0.45)},
                                   {2.987*pow(dim_length,-0.34),1.042*pow(
                                   dim_length,0.09),0.599*pow(dim_length,0.34),
                                   0.555*pow(dim_length,0.36)},      
                                   {0.559*pow(dim_length,0.4),0.545*pow(
                                   dim_length,0.39),0.456*pow(dim_length,0.47),
                                   0.518*pow(dim_length,0.41)},
                                   {0.244*pow(dim_length,0.76),0.338*pow(
                                   dim_length,0.61),0.368*pow(dim_length,0.57),
                                   0.426*pow(dim_length,0.51)},
                                   {0.183*pow(dim_length,0.89),0.3*pow(
                                   dim_length,0.67),0.352*pow(dim_length,0.6),
                                   0.414*pow(dim_length,0.52)},
                                   {0.18*pow(dim_length,0.9),0.393*pow(
                                   dim_length,0.55),0.541*pow(dim_length,0.4),
                                   0.533*pow(dim_length,0.39)},
                                  }; 
             
  double sepInterference[7];

  for (int i=0;i<7;i++)
  {
    if (nonDimSep < 0.3)
    {
      sepInterference[i] = ((nonDimSep-0.3)*(nonDimSep-0.4)*
                           hullInterference[i][0]/0.02)-((nonDimSep-0.2)*(
                           nonDimSep-0.4)*hullInterference[i][1]/0.01)+((
                           nonDimSep-0.2)*(nonDimSep-0.3)*
                           hullInterference[i][2]/0.02);
    }
    else
    {
      sepInterference[i] = ((nonDimSep-0.4)*(nonDimSep-0.5)*
                           hullInterference[i][1]/0.02)-((nonDimSep-0.3)*(
                           nonDimSep-0.5)*hullInterference[i][2]/0.01)+((
                           nonDimSep-0.3)*(nonDimSep-0.4)*
                           hullInterference[i][3]/0.02);
    }
  }

  //calculates hull wave interference based on froude number
  if (Fn<0.4)
    tr = 20;
  else if (Fn<0.5)
    tr = sepInterference[0]+((Fn-0.4)*(sepInterference[1]-sepInterference[0])
         /0.1);
  else if (Fn<0.6)
    tr = sepInterference[1]+((Fn-0.5)*(sepInterference[2]-sepInterference[1])
         /0.1);
  else if (Fn<0.7)
    tr = sepInterference[2]+((Fn-0.6)*(sepInterference[3]-sepInterference[2])
         /0.1);
  else if (Fn<0.8)
    tr = sepInterference[3]+((Fn-0.7)*(sepInterference[4]-sepInterference[3])
         /0.1);
  else if (Fn<0.9)
    tr = sepInterference[4]+((Fn-0.8)*(sepInterference[5]-sepInterference[4])
         /0.1);
  else if (Fn<1.0)
    tr = sepInterference[5]+((Fn-0.9)*(sepInterference[6]-sepInterference[5])
         /0.1);
  else 
    tr = 20;

  //adds in hull wave interference
  if (hulls == 2)
  {
    Cr = Cr*tr;
  }

  //calculates total resistance coefficient
  totalCoeff = frictCoeffShip+Cr-((formFactor-1)*(frictCoeffModel-
               frictCoeffShip));
  
  //calculates hill resistance
  hullResistance = 0.5*1025*totalCoeff*surfaceArea*pow(velocity,2);

  if (hulls == 2)
    hullResistance = hullResistance*2;

  return (hullResistance);
}
