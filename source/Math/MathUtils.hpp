#pragma once

#include <math.h>

struct MathUtils{
	static float radians(float degrees){
		return (float)(degrees * (M_PI / 180));
	}

	static float degrees(float radians){
		return (float)(radians * (180 / M_PI));
	}
};