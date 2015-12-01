#include "Brain.hpp"

#include <Component\Circle2d.hpp>
#include <glm\gtx\vector_angle.hpp>

void Brain::load(){
	_transform = getComponent<Transform>();
	_movement = getComponent<Movement>();
}

void Brain::update(double dt){
	//if (rand() % 100 == 0){
	//	_mode = rand() % 4;
	//
	//	if (rand() % 2 == 0)
	//		_boost = true;
	//	else
	//		_boost = false;
	//}

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


	EntityVector food;
	EntityManager::getEntities("food", food);

	glm::vec3 nearestFood = food[0]->getComponent<Transform>()->position();
	float distance = glm::distance(_transform->position(), nearestFood);

	for (Entity* entity : food){
		Transform* foodTransform = entity->getComponent<Transform>();

		float tempDistance = glm::distance(_transform->position(), foodTransform->position());

		if (distance > tempDistance){
			distance = tempDistance;
			nearestFood = foodTransform->position();
		}
	}

	//float angleBetween = glm::degrees(glm::angle(_transform->position(), nearestFood));

	glm::vec3 difference = glm::normalize(_transform->position() - nearestFood);
	
	float differenceAngle = glm::atan(difference.x, difference.y);
	float facingAngle = glm::eulerAngles(_transform->rotation()).z;



	//// REMOVE THIS
	std::string name = EntityManager::nameBank().getName(id());
	
	if (name != "player")
		return;
	
	message_out("%f %f\n", glm::abs(glm::degrees(facingAngle + differenceAngle)) - 180, glm::distance(_transform->position(), nearestFood));
}