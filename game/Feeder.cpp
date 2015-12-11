#include "Feeder.hpp"

Feeder::Feeder(float decay, float nutrition, float max){
	_decay = decay;
	_nutrition = nutrition;
	_max = max;
}

void Feeder::load(){
	_transform = getComponent<Transform>();
	_circle = getComponent<Circle2d>();
}

void Feeder::update(double dt){
	if (_capacity == 0)
		return;

	if (_eating){
		Circle2d* circle = _eating->getComponent<Circle2d>();

		if (!circle)
			return;
		
		circle->setRadius(circle->radius() - (float)(_speed * dt));
		
		if (circle->radius() <= _death * 4)
			EntityManager::destroyEntity(_eating->id());

		_capacity += (float)(_nutrition * dt);

		if (_capacity > _max)
			_capacity = _max;
	}
	else{
		_capacity -= (float)(_decay * dt);

		if (_capacity <= _death)
			_capacity = 0.f;
	}

	if (_predator && _capacity != 0.f && _circle->radius() < _predator->_circle->radius()){
		_beingEaten = true;
		_lastPredator = _predator->id();

		_capacity -= (float)(_nutrition * dt);
		_predator->_capacity += (float)(_nutrition * dt);

		if (_capacity < 0.f)
			_capacity = 0.f;

		if (_predator->_capacity > _predator->_max)
			_predator->_capacity = _predator->_max;
	}
	else{
		_beingEaten = false;
	}

	_circle->setRadius(_capacity * 4.f);

	if (_circle->radius() < 0.f)
		_circle->setRadius(0.f);

	_eating = 0;
	_predator = 0;
}

Entity* Feeder::beingEaten(){
	if (!_beingEaten)
		return 0;

	return EntityManager::getEntity(_lastPredator);
}

void Feeder::onCollision(int id){
	std::string name = EntityManager::nameBank().getName(id);

	if (name == "food"){
		Entity* other = EntityManager::getEntity(id);

		_eating = other->getComponent<Circle2d>();
	}
	else if (name == "computer" || name == "player"){
		Entity* other = EntityManager::getEntity(id);

		_predator = other->getComponent<Feeder>();
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

glm::vec3 Feeder::nearestThreat(Vec3Vector& vector){
	EntityVector computers;
	EntityManager::getEntities("computer", computers);


	Entity* player = EntityManager::getEntity("player");

	if (player)
		computers.push_back(player);


	if (computers.size() == 0){
		_active = false;
		return glm::vec3(0, 0, 0);
	}

	if (!_active)
		_active = true;


	glm::vec3 nearest = computers[0]->getComponent<Transform>()->position();
	float distance = glm::distance(_transform->position(), nearest);
	
	for (Entity* entity : computers){
		Feeder* otherFeeder = entity->getComponent<Feeder>();

		if (otherFeeder == this)
			continue;

		if (otherFeeder->_capacity < _capacity)
			continue;

		glm::vec3 otherPosition = entity->getComponent<Transform>()->position();

		vector.push_back(otherPosition);

		float newDistance = glm::distance(_transform->position(), otherPosition);

		if (newDistance < distance){
			nearest = otherPosition;
			distance = newDistance;
		}
	}

	return nearest;
}

glm::vec3 Feeder::nearestFood(Vec3Vector& vector){
	EntityVector food;
	EntityManager::getEntities("food", food);

	if (food.size() == 0){
		_active = false;
		return glm::vec3(0, 0, 0);
	}

	if (!_active)
		_active = true;

	glm::vec3 nearestFood = food[0]->getComponent<Transform>()->position();
	float distance = glm::distance(_transform->position(), nearestFood);

	for (Entity* entity : food){
		Transform* transform = entity->getComponent<Transform>();

		vector.push_back(transform->position());

		float tempDistance = glm::distance(_transform->position(), transform->position());

		if (distance > tempDistance){
			distance = tempDistance;
			nearestFood = transform->position();
		}
	}

	EntityVector computers;
	EntityManager::getEntities("computer", computers);

	Entity* player = EntityManager::getEntity("player");

	if (player)
		computers.push_back(player);

	if (computers.size() == 0)
		return nearestFood;

	for (Entity* entity : computers){
		Feeder* feeder = entity->getComponent<Feeder>();

		if (feeder->_capacity == 0.f)
			continue;

		if (feeder->_capacity < _capacity){
			float tempDistance = glm::distance(_transform->position(), feeder->_transform->position());

			if (distance > tempDistance){
				distance = tempDistance;
				nearestFood = feeder->_transform->position();
			}
		}
	}

	return nearestFood;
}

bool Feeder::active(){
	return _active;
}

float Feeder::maxCapacity(){
	return _max;
}