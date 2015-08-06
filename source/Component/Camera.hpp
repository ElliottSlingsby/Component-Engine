#pragma once

#include <Base\HelperComponent.hpp>
#include <Component\Transform.hpp>
#include <GL\glew.h>
#include "Window.hpp"
#include <math.h>

class Camera : public HelperComponent{
	Transform* _transform = 0;

public:
	void load(){
		_transform = _getComponent<Transform>();
	}

	void render(){
		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();
		
		glRotatef(_transform->rotation().x(), 1.f, 0.f, 0.f);
		glRotatef(_transform->rotation().y(), 0.f, 1.f, 0.f);
		glRotatef(_transform->rotation().z(), 0.f, 0.f, 1.f);

		glTranslatef(_transform->position().x(), _transform->position().y(), _transform->position().z());
	}

	Component* clone(){
		return new Camera;
	}
};