#include "Brain.hpp"

void Brain::load(){
	_transform = getComponent<Transform>();
	_movement = getComponent<Movement>();
	_feeder = getComponent<Feeder>();
}

float changeRange(float oldMin, float oldMax, float newMin, float newMax, float oldValue){
	return (((oldValue - oldMin) * (newMax - newMin)) / (oldMax - oldMin)) + newMin;
}

void Brain::update(double dt){
	// Nearest input
	glm::vec3 nearest = _feeder->nearestFood();

	glm::vec3 difference = glm::normalize(_transform->position() - nearest);
	
	float differenceAngle = glm::atan(difference.x, difference.y);
	float facingAngle = glm::eulerAngles(_transform->rotation()).z;

	_nearestFood = glm::abs(glm::degrees(facingAngle + differenceAngle));

	if (glm::sign(_nearestFood) == -1.f)
		_nearestFood += 360;

	_nearestFood = changeRange(0, 360, -1, 1, _nearestFood);
	
	// Eating input
	if (_feeder->eating())
		_eating = 1.f;
	else
		_eating = -1.f;
	
	// REMOVE THIS
	std::string name = EntityManager::nameBank().getName(id());
	
	if (name != "player")
		return;
	
	message_out("%f %f\n", _nearestFood, _eating);
}