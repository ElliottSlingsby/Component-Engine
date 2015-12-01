#include "Feeder.hpp"

Feeder::Feeder(float speed){
	_speed = speed;
}

void Feeder::update(double dt){
	if (_eating){
		Circle2d* circle = _eating->getComponent<Circle2d>();

		if (!circle)
			return;
		
		circle->setRadius(circle->radius() - (float)(75 * dt));
		
		if (circle->radius() <= 0.f)
			EntityManager::destroyEntity(_eating->id());
	}

	_eating = 0;
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