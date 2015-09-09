#include "Camera.hpp"

#include <GL\glew.h>
#include <Static\Renderer.hpp>
#include <glm\gtc\matrix_transform.hpp>

void Camera::load(){
	_transform = getComponent<Transform>();
}

void Camera::preRender(){
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	glMultMatrixf(&glm::inverse(glm::mat4_cast(_transform->rotation()))[0][0]);

	glTranslatef(_transform->position().x, _transform->position().y, _transform->position().z);
}