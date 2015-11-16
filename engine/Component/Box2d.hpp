#pragma once

#include <Entity\HelperComponent.hpp>
#include <glm\vec2.hpp>
#include <GL\glew.h>

class Box2d : public HelperComponent{
	Transform* _transform = 0;

	glm::vec2 _size;

public:
	Box2d(float width = 0.5f, float height = 0.5f){
		_size = glm::vec2(width, height);
	}

	void load(){
		_transform = getComponent<Transform>();
	}

	glm::vec4 project(const glm::vec2& axis){
		glm::vec2 corners[4] = { corner(0), corner(1), corner(2), corner(3) };

		float minMag = glm::dot(axis, corners[0]);
		float maxMag = minMag;

		for (int i = 0; i < 4; i++){
			float magnitude = glm::dot(axis, corners[i]);

			if (magnitude < minMag)
				minMag = magnitude;
			else if (magnitude > maxMag)
				maxMag = magnitude;
		}

		glm::vec2 start = axis * minMag;
		glm::vec2 end = axis * maxMag;

		return glm::vec4(start.x, start.y, end.x, end.y);
	}

	void render(){
		glm::vec2 corners[4] = { corner(0), corner(1), corner(2), corner(3) };

		glm::vec4 up = project(glm::vec2(0, 1));
		glm::vec4 right = project(glm::vec2(1, 0));
		
		glDisable(GL_LIGHTING);
		glDisable(GL_CULL_FACE);

		glLineWidth(5);

		glBegin(GL_LINES);
		
		glVertex3f(right.x, right.y, 0);
		glVertex3f(right.z, right.w, 0);

		glVertex3f(up.x, up.y, 0);
		glVertex3f(up.z, up.w, 0);

		glEnd();


		glBegin(GL_QUADS);

		glVertex3f(corners[0].x, corners[0].y, 0);
		glVertex3f(corners[1].x, corners[1].y, 0);
		glVertex3f(corners[2].x, corners[2].y, 0);
		glVertex3f(corners[3].x, corners[3].y, 0);

		glEnd();

		glEnable(GL_LIGHTING);
		glEnable(GL_CULL_FACE);
	}

	glm::vec2 corner(unsigned int i){
		if (i == 0)
			return _transform->apply2d(glm::vec2(-_size.x / 2, -_size.y / 2));
		if (i == 1)
			return _transform->apply2d(glm::vec2(_size.x / 2, -_size.y / 2));
		if (i == 2)
			return _transform->apply2d(glm::vec2(_size.x / 2, _size.y / 2));
		if (i == 3)
			return _transform->apply2d(glm::vec2(-_size.x / 2, _size.y / 2));
	}

	bool isColliding(Box2d* other){
		return false;
	}
};