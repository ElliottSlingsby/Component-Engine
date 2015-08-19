#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include "Vector3.hpp"

struct MathUtils{
	static float radians(float degrees){
		return (float)(degrees * (M_PI / 180));
	}

	static float degrees(float radians){
		return (float)(radians * (180 / M_PI));
	}

	template <typename T>
	static Vector3<T> dot(Vector3<T>, Vector3<T>){
		glm::quat test()
	}
};