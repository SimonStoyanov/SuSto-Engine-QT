#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include <list>
#include <string>

// -----------------------------------------
// -----------------------------------------

// USEFULL FUNCTIONS //

// -----------------------------------------
// -----------------------------------------

// Returns a random int given a range;
int GetRandomValue(int range_1, int range_2);

// Returns a random float given a range;
float GetRandomValue(float range_1, float range_2);

// Returns a random float given a range;
double GetRandomValue(double range_1, double range_2);

double GetUIDRandomDouble();

float GetUIDRandomFloat();

int GetUIDRandomInt();

std::string IntToHexa(int num);

std::string GetUIDRandomHexadecimal();

#endif //__FUNCTIONS_H__
