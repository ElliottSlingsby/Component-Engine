#pragma once

#include <Entity\HelperComponent.hpp>
#include <Component\Transform.hpp>
#include <GL\glew.h>
#include "Static\Renderer.hpp"

class Camera : public HelperComponent{
	Transform* _transform = 0;

public:
	void load(){
		_transform = getComponent<Transform>();
	}
	
	void preRender(){
		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();

		glm::vec3 eulerAngles = glm::eulerAngles(_transform->rotation());

		glRotatef(glm::degrees(eulerAngles.x), -1.f, 0.f, 0.f);
		glRotatef(glm::degrees(eulerAngles.y), 0.f, -1.f, 0.f);
		glRotatef(glm::degrees(eulerAngles.z), 0.f, 0.f, -1.f);

		glTranslatef(_transform->position().x, _transform->position().y, _transform->position().z);
	}
};