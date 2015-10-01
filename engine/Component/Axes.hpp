#pragma once

#include <Component\Model.hpp>

class Axes : public Model{
	float _length;

public:
	Axes(float length, bool fixedRotation = true);
	
	void draw();
};