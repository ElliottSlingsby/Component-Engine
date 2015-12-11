#include "Utils.hpp"

#include <random>

float changeRange(float oldMin, float oldMax, float newMin, float newMax, float oldValue){
	return (((oldValue - oldMin) * (newMax - newMin)) / (oldMax - oldMin)) + newMin;
}

float randomRange(int range, int spread){
	return (float)((rand() % range * spread) - (range / 2) * spread);
}