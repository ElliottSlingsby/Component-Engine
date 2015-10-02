#pragma once

#include <Component\Model.hpp>

class Grid : public Model{
	float _spacing;
	int _size;
	int _majorLine;

public:
	enum GridAxis{ X, Y, Z };

	Grid(int size = 512, float spacing = 64, int majorLine = 16, GridAxis plane = Y);
	
	void draw();

private:
	GridAxis _plane;
};