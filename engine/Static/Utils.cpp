#include "Utils.hpp"

#include <random>

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