#include "Camera.hpp"

#include <GL\glew.h>
#include <Static\Renderer.hpp>
#include <glm\gtc\matrix_transform.hpp>

void Camera::load(){
	_transform = getComponent<Transform>();
	
	reshape();
}

void Camera::preRender(){
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	glMultMatrixf(&glm::inverse(glm::mat4_cast(_transform->rotation()))[0][0]);

	glTranslatef(_transform->position().x, _transform->position().y, _transform->position().z);
}

void Camera::reshape(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float ar = (float)Renderer::Window().width() / (float)Renderer::Window().height();
	gluPerspective(_fov / ar, ar, 0.1, _drawDistance);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	int hpad = 0;
	int vpad = 75;

	glScissor(_horizontalPadding, _verticalPadding, Renderer::Window().width() - _horizontalPadding * 2, Renderer::Window().height() - _verticalPadding * 2);
	glFogf(GL_FOG_DENSITY, _fogDensity);
}

void Camera::setFogDensity(float fogDensity){
	_fogDensity = fogDensity;
	glFogf(GL_FOG_DENSITY, fogDensity);
}

void Camera::setVerticalPadding(unsigned int verticalPadding){
	_verticalPadding = verticalPadding;
	glScissor(_horizontalPadding, _verticalPadding, Renderer::Window().width() - _horizontalPadding * 2, Renderer::Window().height() - _verticalPadding * 2);
}

void Camera::setHorizontalPadding(unsigned int horizontalPadding){
	_horizontalPadding = horizontalPadding;
	setVerticalPadding(_verticalPadding);
}

void Camera::setFov(unsigned int fov){
	_fov = fov;

	float ar = (float)Renderer::Window().width() / (float)Renderer::Window().height();
	gluPerspective(fov / ar, ar, 0.1, _drawDistance);
}

void Camera::setDrawDistance(unsigned int drawDistance){
	_drawDistance = drawDistance;
	setFov(_fov);
}