#pragma once

#include "Vector3.hpp"
#include "MathUtils.hpp"
#include <math.h>

class Quaternion{
	float _w, _x, _y, _z;

public:
	Quaternion(Vector3f vector, float angle){
		angle = MathUtils::radians(angle);

		_w = cos(angle / 2);
		_x = vector.x() * sin(angle / 2);
		_y = vector.y() * sin(angle / 2);
		_z = vector.z() * sin(angle / 2);
	}
};