#include <ctype.h>
#include "functions.h"
#include <stdio.h>
#include <cmath>
#include <random>
#include <limits>
#include <stdlib.h>
#include <string>
#include <sstream>

int GetRandomValue(int range_1, int range_2)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(range_1, range_2);

	return dis(gen);
}

float GetRandomValue(float range_1, float range_2)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(range_1, range_2);

	return dis(gen);
}

double GetRandomValue(double range_1, double range_2)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(range_1, range_2);

	return dis(gen);
}

double GetUIDRandomDouble()
{
	return GetRandomValue((double)0, DBL_MAX);
}

float GetUIDRandomFloat()
{
	return GetRandomValue((float)0, FLT_MAX);
}

int GetUIDRandomInt()
{
	return GetRandomValue(0, INT_MAX);
}

std::string IntToHexa(int value)
{
    std::stringstream stream;
	stream << std::hex << value;
	std::string result(stream.str());
	return result;
}

std::string GetUIDRandomHexadecimal()
{
	double val = GetUIDRandomInt();
	std::string ret = IntToHexa(val);

	return ret;
}
