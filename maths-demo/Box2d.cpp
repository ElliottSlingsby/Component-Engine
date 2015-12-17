#include "Box2d.hpp"

#include <GL\glew.h>

Box2d::Box2d(float width, float height){
	_size = glm::vec2(width, height);
}

void Box2d::load(){
	_transform = getComponent<Transform>();
}

void Box2d::lateUpdate(double dt){
	// Updating this world coordinates for each corner
	glm::vec2 half((_size.x * _transform->scale().x) / 2, (_size.y * _transform->scale().y) / 2);

	_corners[0] = _transform->apply2d(glm::vec2(-half.x, -half.y));
	_corners[1] = _transform->apply2d(glm::vec2(half.x, -half.y));
	_corners[2] = _transform->apply2d(glm::vec2(half.x, half.y));
	_corners[3] = _transform->apply2d(glm::vec2(-half.x, half.y));

	// Updating this axes rotation
	_axes[0] = glm::vec2(0, 1);
	_axes[1] = glm::vec2(1, 0);

	glm::quat rotation(glm::vec3(0, 0, glm::eulerAngles(_transform->rotation()).z));

	for (int i = 0; i < 2; i++){
		glm::vec3 axis = glm::vec3(_axes[i].x, _axes[i].y, 0) * glm::inverse(rotation);
		_axes[i] = glm::vec2(axis.x, axis.y);
	}

	_testColliding = false;

	std::string name = EntityManager::nameBank().getName(id());

	if (name == "player" || name == "box"){
		Entity* entity = EntityManager::getEntity("box");

		if (!entity)
			return;

		Box2d* box = entity->getComponent<Box2d>();

		if (!box)
			return;

		entity = EntityManager::getEntity("player");

		if (!entity)
			return;

		Box2d* player = entity->getComponent<Box2d>();

		if (!player)
			return;

		if (name == "player"){
			if (isColliding(box))
				_testColliding = true;
			else
				_testColliding = false;
		}

		if (name == "box"){
			if (isColliding(player))
				_testColliding = true;
			else
				_testColliding = false;
		}
	}
}

void Box2d::render(){
	glColor3f(1.f, 1.f, 1.f);

	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);

	if (EntityManager::nameBank().getName(id()) == "player" || EntityManager::nameBank().getName(id()) == "box"){
		// Rotating debug axes
		float length = 2056;

		glLineWidth(2);

		glBegin(GL_LINES);

		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(-_axes[0].x * length, -_axes[0].y * length, 0.5f);
		glVertex3f(_axes[0].x * length, _axes[0].y * length, 0.5f);

		glColor3f(0.f, 1.f, 0.5f);
		glVertex3f(-_axes[1].x * length, -_axes[1].y * length, 0.5f);
		glVertex3f(_axes[1].x * length, _axes[1].y * length, 0.5f);

		glColor3f(1.f, 1.f, 1.f);

		glEnd();

		// Overlapping debug lines
		glLineWidth(4);

		glBegin(GL_LINES);

		glVertex3f(_axes[0].x * _magnitudes[0].x, _axes[0].y * _magnitudes[0].x, 1.f);
		glVertex3f(_axes[0].x * _magnitudes[0].y, _axes[0].y * _magnitudes[0].y, 1.f);

		glVertex3f(_axes[1].x * _magnitudes[1].x, _axes[1].y * _magnitudes[1].x, 1.f);
		glVertex3f(_axes[1].x * _magnitudes[1].y, _axes[1].y * _magnitudes[1].y, 1.f);

		glVertex3f(_axes[0].x * _magnitudes[2].x, _axes[0].y * _magnitudes[2].x, 1.f);
		glVertex3f(_axes[0].x * _magnitudes[2].y, _axes[0].y * _magnitudes[2].y, 1.f);

		glVertex3f(_axes[1].x * _magnitudes[3].x, _axes[1].y * _magnitudes[3].x, 1.f);
		glVertex3f(_axes[1].x * _magnitudes[3].y, _axes[1].y * _magnitudes[3].y, 1.f);

		glEnd();
	}

	glBegin(GL_QUADS);

	if (_testColliding)
		glColor3f(1.f, 1.f, 0.f);
	else
		glColor3f(1.f, 1.f, 1.f);

	glVertex3f(_corners[0].x, _corners[0].y, 1.f);
	glVertex3f(_corners[1].x, _corners[1].y, 1.f);
	glVertex3f(_corners[2].x, _corners[2].y, 1.f);
	glVertex3f(_corners[3].x, _corners[3].y, 1.f);

	glEnd();

	glLineWidth(1);
	glColor3f(1.f, 1.f, 1.f);

	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
}

bool Box2d::overlapping(const glm::vec2& first, const glm::vec2& second){
	if (first.x <= second.x && first.y >= second.x)
		return true;
	if (first.x <= second.y && first.y >= second.y)
		return true;
	if (second.x <= first.x && second.y >= first.x)
		return true;
	if (second.x <= first.y && second.y >= first.y)
		return true;

	return false;
}

bool Box2d::isColliding(Box2d* other, bool recurse){
	// Projecting other onto this axes and updating magnitudes
	Box2d* targets[2] = { this, other };

	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 2; j++){
			float minimum = glm::dot(_axes[j], targets[i]->_corners[0]);
			float maximum = minimum;

			for (int k = 0; k < 4; k++){
				float magnitude = glm::dot(_axes[j], targets[i]->_corners[k]);

				if (magnitude < minimum)
					minimum = magnitude;
				else if (magnitude > maximum)
					maximum = magnitude;
			}

			_magnitudes[(i * 2) + j] = glm::vec2(minimum, maximum);
		}
	}

	// Check for exit case before carrying on
	if (recurse){
		bool result = other->isColliding(this, false);

		if (!result)
			return false;
	}

	// Check for overlaps
	if (!overlapping(_magnitudes[0], _magnitudes[2]))
		return false;

	if (!overlapping(_magnitudes[1], _magnitudes[3]))
		return false;

	return true;
}