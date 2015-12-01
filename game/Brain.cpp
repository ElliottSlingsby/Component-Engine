#include "Brain.hpp"

#include <Component\Circle2d.hpp>

void Brain::load(){
	_movement = getComponent<Movement>();
}

void Brain::update(double dt){
	if (rand() % 100 == 0){
		_mode = rand() % 4;

		if (rand() % 2 == 0)
			_boost = true;
		else
			_boost = false;
	}

	if (_mode == 1){
		_movement->forward();

		if (_boost)
			_movement->forward();
	}
	else if (_mode == 2){
		_movement->left();

		if (_boost)
			_movement->left();
	}
	else if (_mode == 3){
		_movement->right();

		if (_boost)
			_movement->right();
	}
}

void Brain::onCollision(int id){
	//std::string name = EntityManager::nameBank().getName(id);
	//
	//if (name == "food"){
	//	Entity* other = EntityManager::getEntity(id);
	//
	//	if (!other)
	//		return;
	//
	//	Circle2d* circle = other->getComponent<Circle2d>();
	//
	//	if (!circle)
	//		return;
	//
	//	circle->setRadius(circle->radius() - 0.5f);
	//
	//	if (circle->radius() <= 0.f)
	//		EntityManager::destroyEntity(id);
	//}
}