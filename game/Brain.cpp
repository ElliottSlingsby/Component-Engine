#include "Brain.hpp"

Brain::~Brain(){
	_network.destroy();
}

void Brain::load(){
	_transform = getComponent<Transform>();
	_movement = getComponent<Movement>();
	_feeder = getComponent<Feeder>();
	_circle = getComponent<Circle2d>();
	
	_network.create_from_file("../data/simple_training.net");
}

float Brain::_changeRange(float oldMin, float oldMax, float newMin, float newMax, float oldValue){
	return (((oldValue - oldMin) * (newMax - newMin)) / (oldMax - oldMin)) + newMin;
}

void Brain::update(double dt){
	if (_feeder->capacity() == 0.f)
		return;

	// Nearest input
	glm::vec3 nearest = _feeder->nearestFood();

	glm::vec3 difference = glm::normalize(_transform->position() - nearest);
	
	float differenceAngle = glm::atan(difference.x, difference.y);
	float facingAngle = glm::eulerAngles(_transform->rotation()).z;







	if (glm::sign(_nearestFood) == -1.f)
		_nearestFood += 360;

	_nearestFood = glm::degrees(facingAngle + differenceAngle);



	if (glm::sign(_nearestFood) == -1.f)
		_nearestFood += 360;

	float degrees = _nearestFood;
	
	_nearestFood = _changeRange(0, 360, -1, 1, _nearestFood);


	float max = 1024.f;

	float speed = _changeRange(0, max, 0.f, 1.f, glm::distance(_transform->position(), nearest));
	
	if (speed > 1.f)
		speed = 1.f;

	// Eating input
	if (_feeder->eating())
		_eating = 1.f;
	else
		_eating = 0.f;


	_movement->turn(_nearestFood);
	
	if (!_feeder->eating())
		_movement->forward(speed);


		
	// REMOVE THIS
	std::string name = EntityManager::nameBank().getName(id());
	
	if (name != "player")
		return;
	
	//message_out("%f\n", degrees);
}