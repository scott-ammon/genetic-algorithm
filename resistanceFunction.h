#ifndef _RESISTANCE_H_
#define _RESISTANCE_H_

// This function returns the resistance in newtons of the vessel
// given the input characteristics

double getResistance(double length, double beam, double draft, double Cb, double velocity_knots, int hulls);

#endif

