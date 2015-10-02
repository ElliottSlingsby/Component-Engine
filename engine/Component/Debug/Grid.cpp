#include "Grid.hpp"

#include <GL\glew.h>

Grid::Grid(int size, float spacing, int majorLine, GridAxis plane){
	_plane = plane;
	_size = size;
	_spacing = spacing;
	_majorLine = majorLine;

	setUnlit(true);
	setFixedRotation(true);
}

void Grid::draw(){
	
	
	for (int i = -(_size / 2); i <= _size / 2; i += 1){	
		float step = (float)i * _spacing;
		float run = _spacing * (float)(_size / 2);

		if (i % _majorLine)
			glColor3f(0.65f, 0.65f, 0.65f);

		glBegin(GL_LINES);

		switch (_plane){
		case X:
			glVertex3f(0.f, step, -run);
			glVertex3f(0.f, step, run);
			glVertex3f(0.f, -run, step);
			glVertex3f(0.f, run, step);
			break;
		case Y:
			glVertex3f(step, 0.f, -run);
			glVertex3f(step, 0.f, run);
			glVertex3f(-run, 0.f, step);
			glVertex3f(run, 0.f, step);
			break;
		case Z:
			glVertex3f(step, -run, 0.f);
			glVertex3f(step, run, 0.f);
			glVertex3f(-run, step, 0.f);
			glVertex3f(run, step, 0.f);
			break;
		}

		glEnd();

		if (i % _majorLine)
			glColor3f(1.f, 1.f, 1.f);
	}
	
}