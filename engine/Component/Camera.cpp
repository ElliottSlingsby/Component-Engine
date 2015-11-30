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

	if (!_2d){
		glMultMatrixf(&glm::inverse(glm::mat4_cast(_transform->rotation()))[0][0]);
		glTranslatef(_transform->position().x, _transform->position().y, _transform->position().z);
	}
	else{
		glMultMatrixf(&glm::inverse(glm::mat4_cast(glm::quat(glm::vec3(0, 0, glm::eulerAngles(_transform->rotation()).z))))[0][0]);
		glTranslatef(_transform->position().x, _transform->position().y, 0);
	}


	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	
	model = model * glm::inverse(glm::mat4_cast(_transform->rotation()));
	model = glm::translate(view, _transform->position());

	projection = glm::ortho(0.f, 1280.f, 0.f, 720.f);
	
	//float aspectRatio = ((float)Renderer::window().width() / (float)Renderer::window().height());
	//
	//projection = glm::perspective(_fov / aspectRatio, aspectRatio, 0.1f, (float)_drawDistance);
	//projection= glm::rotate(projection, glm::radians(90.f), glm::vec3(1, 0, 0));

	Renderer::shaderManager().uniform("model", model);
	Renderer::shaderManager().uniform("view", view);
	Renderer::shaderManager().uniform("projection", projection);
}

void Camera::reshape(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float aspectRatio = ((float)Renderer::window().width() / (float)Renderer::window().height());

	glm::mat4 matrix(
		-1,	0,	0,	0,
		0,	-1,	0,	0,
		0,	0,	1,	0,
		0,	0,	0,	1
	);

	glMultMatrixf(&matrix[0][0]);

	if (!_2d){
		gluPerspective(_fov / aspectRatio, aspectRatio, 0.1, _drawDistance);
		glRotatef(90.f, 1.f, 0.f, 0.f);
	}
	else{
		glOrtho(0, Renderer::window().width() * _zoom, 0, Renderer::window().height() * _zoom, -_drawDistance, _drawDistance);
		//glTranslatef(Renderer::Window().width() * _zoom, Renderer::Window().height() * _zoom, 0);	//true 2d mode
		glTranslatef((Renderer::window().width() / 2) * _zoom, (Renderer::window().height() / 2) * _zoom, 0);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glScissor(_horizontalPadding, _verticalPadding, Renderer::window().width() - _horizontalPadding * 2, Renderer::window().height() - _verticalPadding * 2);
	glFogf(GL_FOG_DENSITY, _fogDensity);
}

void Camera::set2d(bool mode){
	_2d = mode;
	reshape();
}

void Camera::setZoom(float zoom){
	_zoom = zoom;
	reshape();
}

void Camera::setFogDensity(float fogDensity){
	_fogDensity = fogDensity;
	glFogf(GL_FOG_DENSITY, fogDensity);
}

void Camera::setVerticalPadding(unsigned int verticalPadding){
	_verticalPadding = verticalPadding;
	glScissor(_horizontalPadding, _verticalPadding, Renderer::window().width() - _horizontalPadding * 2, Renderer::window().height() - _verticalPadding * 2);
}

void Camera::setHorizontalPadding(unsigned int horizontalPadding){
	_horizontalPadding = horizontalPadding;
	setVerticalPadding(_verticalPadding);
}

void Camera::setFov(unsigned int fov){
	_fov = fov;
	reshape();
}

void Camera::setDrawDistance(unsigned int drawDistance){
	_drawDistance = drawDistance;
	reshape();
}