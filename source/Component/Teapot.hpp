#pragma once

#include <Base\HelperComponent.hpp>
#include <Component\Transform.hpp>
#include <fstream>
#include <GL\glew.h>
#include <regex>

/*
Vertices
	v +(-*\d+.\d+) +(-*\d+.\d+) +(-*\d+.\d+)
	v +(?:(-*\d+.\d+) *){3}

Normals
	vn +(-*\d+.\d+) +(-*\d+.\d+) +(-*\d+.\d+)
	vn +(?:(-*\d+.\d+) *){3}

UVs
	vt +(-*\d+.\d+) +(-*\d+.\d+) +(-*\d+.\d+)
	vt +(?:(-*\d+.\d+) *){3}

Faces
	f +(\d+)\/(\d+)\/(\d+) +(\d+)\/(\d+)\/(\d+) +(\d+)\/(\d+)\/(\d+)
	f +(?:(\d+)\/(\d+)\/(\d+) *){3}
	f +(?:(?:(\d+)\/*){3} *){3}

Others
	g +([\s\S]+)
	s +(\d+)
*/

class Teapot : public HelperComponent{
	Transform* _transform = 0;

	GLfloat vertices[529];
	GLfloat normals[530];
	GLfloat textures[287];
	GLint faces[1024];

public:
	void load(){
		_transform = _getComponent<Transform>();

		std::ofstream file;
		file.open("../assets/teapot.obj", 'r');
	}

	Component* clone(){
		return new Teapot;
	}
};