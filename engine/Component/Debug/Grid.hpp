#pragma once

#include <Component\Model.hpp>

class Grid : public Model{
	float _spacing;
	int _size;
	int _majorLine;

public:
	enum GridAxis{ AxisX, AxisY, AxisZ };

	Grid(int size = 512, float spacing = 64, int majorLine = 16, GridAxis plane = AxisY);
	
	void draw();

private:
	GridAxis _plane;
};