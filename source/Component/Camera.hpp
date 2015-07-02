#pragma once

#include <Base\HelperComponent.hpp>
#include <Component\Transform.hpp>
#include <GL\glew.h>
#include "Window.hpp"

// Super prototype

class Camera : public HelperComponent{
	Transform* _transform = 0;
	float _ratio;

public:
	void load(){
		_transform = _getComponent<Transform>();
		_ratio = (float)Window::size().x() / (float)Window::size().y();
	}

	void render(){
		// Replace with push pop

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		gluPerspective(59, _ratio, 0.1, 100);

		glRotatef(_transform->euler().x(), 1.f, 0.f, 0.f);
		glRotatef(_transform->euler().y(), 0.f, 1.f, 0.f);
		glRotatef(_transform->euler().z(), 0.f, 0.f, 1.f);

		glTranslatef(_transform->position().x(), _transform->position().y(), _transform->position().z());
	}

	Component* clone(){
		return new Camera;
	}
};