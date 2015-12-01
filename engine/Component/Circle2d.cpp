#include "Circle2d.hpp"

#include <GL\glew.h>

Circle2d::Circle2d(float radius){
	_radius = radius;
}

void Circle2d::load(){
	_transform = getComponent<Transform>();
}

void Circle2d::render(){
	glLineWidth(2.f);
	glDisable(GL_LIGHTING);

	std::string name = EntityManager::nameBank().getName(id());

	if (name == "computer")
		glColor3f(1.f, 0.5f, 0.5f);
	else if (name == "player")
		glColor3f(1.f, 1.f, 1.f);
	else if(name == "food")
		glColor3f(0.5f, 1.f, 0.5f);

	float step = 1.f;

	glBegin(GL_LINES);

	glm::vec2 current = glm::vec2(glm::sin(0.f) * _radius, glm::cos(0.f) * _radius);
	glm::vec3 position = _transform->position();
	
	for (float i = 0.f; i < 360.f; i += step){
		glm::vec2 previous = current;
		current = glm::vec2(glm::sin(glm::radians(i)) * _radius, glm::cos(glm::radians(i)) * _radius);

		glVertex3f(previous.x - position.x, previous.y - position.y, 1.f);
		glVertex3f(current.x - position.x, current.y - position.y, 1.f);
	}

	glm::vec2 previous = current;
	current = glm::vec2(glm::sin(0.f) * _radius, glm::cos(0.f) * _radius);

	glVertex3f(previous.x - position.x, previous.y - position.y, 1.f);
	glVertex3f(current.x - position.x, current.y - position.y, 1.f);

	glEnd();

	glEnable(GL_LIGHTING);
	glLineWidth(1.f);
}

bool Circle2d::isColliding(Circle2d* other){
	glm::vec3 thisPos = _transform->position();
	glm::vec3 otherPos = other->_transform->position();

	if (glm::distance(thisPos, otherPos) <= _radius + other->_radius)
		return true;

	return false;
}