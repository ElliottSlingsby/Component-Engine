#include "Brain.hpp"

#include <Utils.hpp>

Brain::~Brain(){
	_network.destroy();
}

void Brain::load(){
	_transform = getComponent<Transform>();
	_movement = getComponent<Movement>();
	_feeder = getComponent<Feeder>();
	_circle = getComponent<Circle2d>();
	_vision = getComponent<Vision>();
	
	_network.create_from_file("../data/simple_training.net");
}

void Brain::update(double dt){
	if (_feeder->capacity() == 0.f)
		return;


	float baseSpeed = changeRange(0, _feeder->maxCapacity(), 1.f, 0.f, _feeder->capacity());


	Entity* predator = _feeder->beingEaten();

	glm::vec3 target;

	Vec3Vector otherFood;

	if (predator)
		target = predator->getComponent<Transform>()->position();
	else
		target = _feeder->nearestFood(otherFood);

	// Nearest input

	glm::vec3 difference = glm::normalize(_transform->position() - target);
	
	float differenceAngle = glm::atan(difference.x, difference.y);
	float facingAngle = glm::eulerAngles(_transform->rotation()).z;



	if (predator){
		float angle = glm::degrees(facingAngle + differenceAngle + glm::radians(180.f));
		
		if (glm::sign(angle) == -1.f)
			angle += 360;

		_movement->turn(changeRange(0, 360, -1, 1, angle));
		_movement->forward(baseSpeed);

		return;
	}





	if (glm::sign(_nearestFood) == -1.f)
		_nearestFood += 360;

	_nearestFood = glm::degrees(facingAngle + differenceAngle);
	
	if (glm::sign(_nearestFood) == -1.f)
		_nearestFood += 360;

	float degrees = _nearestFood;
	
	_nearestFood = changeRange(0, 360, -1, 1, _nearestFood);


	float max = 1024.f;

	float speed = changeRange(0, max, 0.f, baseSpeed, glm::distance(_transform->position(), target));
	
	if (speed > 1.f)
		speed = 1.f;

	float min = .2f;

	if (speed < min)
		speed = min;

	// Eating input
	if (_feeder->eating())
		_eating = 1.f;
	else
		_eating = 0.f;


	_movement->turn(_nearestFood);
	
	if (!_feeder->eating())
		_movement->forward(speed);
	
	if (!_vision)
		return;
	
	FloatVector pixels;
	_vision->get(pixels);







	// REMOVE THIS
	//std::string name = EntityManager::nameBank().getName(id());
	//
	//if (name != "player")
	//	return;
	//
	//message_out("%f\n", degrees);
}