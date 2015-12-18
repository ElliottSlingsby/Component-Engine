#include "utils.hpp"

#define _USE_MATH_DEFINES
#include <cmath>
#include <random>

float radians(float a){
	return (float)(M_PI / 180.0) * a;
}

float degrees(float a){
	return (float)(180.0 / M_PI) * a;
}

float changeRange(float oldMin, float oldMax, float newMin, float newMax, float oldValue){
	return (((oldValue - oldMin) * (newMax - newMin)) / (oldMax - oldMin)) + newMin;
}

float randomRange(int range, int spread){
	return (float)((rand() % range * spread) - (range / 2) * spread);
}

float clamp(float min, float max, float value){
	if (min > value)
		return min;

	if (value > max)
		return max;

	return value;
}