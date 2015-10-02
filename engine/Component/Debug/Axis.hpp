#pragma once

#include <Component\Model.hpp>

class Axis : public Model{
	float _length;

public:
	Axis(float length, bool fixedRotation = true);
	
	void draw();
};