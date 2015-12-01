#include "Feeder.hpp"

void Feeder::update(double dt){
	if (_eating){
		Circle2d* circle = _eating->getComponent<Circle2d>();

		if (!circle)
			return;
		
		circle->setRadius(circle->radius() - (float)(_speed * dt));
		
		if (circle->radius() <= 0.f)
			EntityManager::destroyEntity(_eating->id());

		_capacity += (float)(_nutrition * dt);

		if (_capacity > _max)
			_capacity = _max;
	}
	else{
		_capacity -= (float)(_decay * dt);

		if (_capacity < 0.f)
			_capacity = 0.f;
	}

	_eating = 0;


	// REMOVE THIS
	std::string name = EntityManager::nameBank().getName(id());

	if (name == "player")
		message_out("%f\n", capacity());
}

void Feeder::onCollision(int id){
	std::string name = EntityManager::nameBank().getName(id);

	if (name == "food"){
		Entity* other = EntityManager::getEntity(id);

		if (!other)
			return;

		_eating = other->getComponent<Circle2d>();
	}
}

bool Feeder::eating(){
	if (_eating)
		return true;

	return false;
}

float Feeder::capacity(){
	if (_capacity == 0.f)
		return 0.f;

	return _capacity / _max;
}