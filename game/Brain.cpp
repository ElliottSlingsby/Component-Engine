#include "Brain.hpp"

#include <Utils.hpp>

#include <Log.hpp>

Brain::Brain(bool training){
	_training = training;
}

Brain::~Brain(){
	_network.destroy();
}

void Brain::load(){
	_transform = getComponent<Transform>();
	_movement = getComponent<Movement>();
	_feeder = getComponent<Feeder>();
	_circle = getComponent<Circle2d>();
	_vision = getComponent<Vision>();
	
	_network.create_from_file("../data/log.net");
}

void Brain::update(double dt){
	if (_feeder->capacity() == 0.f)
		return;

	float baseSpeed = changeRange(0, _feeder->maxCapacity(), 1.f, 0.f, _feeder->capacity());

	if (!_training){
		if (!_vision)
			return;

		//_vision->print();

		FloatVector input;
		_vision->get(input);

		// run ANN

		fann_type fannInput[5 * 5];

		for (int i = 0; i < 5 * 5; i++){
			fannInput[i] = input[i];
		}

		fann_type* output;

		output = _network.run(fannInput);

		// get outputs

		float food = output[0];
		float speed = output[1];

		if (speed > baseSpeed)
			speed = baseSpeed;

		_movement->turn(food);

		if (!_feeder->eating())
			_movement->forward(speed);

		return;
	}
	


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



	// REMOVE THIS
	std::string name = EntityManager::nameBank().getName(id());
	
	if (name != "player"){
		_movement->turn(_nearestFood);

		if (!_feeder->eating())
			_movement->forward(speed);

		return;
	}



	if (!_vision)
		return;

	FloatVector input;
	_vision->get(input);

	FloatVector output = { _nearestFood, speed };

	logFile(input, output);


	
	_vision->print();

	//message_out("%f\n", degrees);
}