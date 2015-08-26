#pragma once

#include "Entity\HelperComponent.hpp"
#include "State\Won.hpp"

class Health : public HelperComponent{
	float _amount;
	float _damage;

public:
	Health(float amount, float damage = 1.f){
		_amount = amount;
		_damage = damage;
	}

	void lateUpdate(){
		if (_amount <= 0.f){
			parent()->destroy();
			EntityManager::changeState<Won>();
		}
	}

	void onCollision(int id){
		EntityVector bullets;
		EntityManager::getEntities("bullet", bullets);

		Entity* other = EntityManager::getEntity(id);

		if (std::find(bullets.begin(), bullets.end(), other) != bullets.end()){
			_amount -= _damage;
			other->destroy();
		}
	}
};