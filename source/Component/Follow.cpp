#include "Follow.hpp"

Follow::Follow(int id, float ease, const glm::vec3& offset){
	_id = id;
	_ease = ease;
	_offset = offset;
}

Follow::Follow(std::string name, float ease, const glm::vec3& offset){
	_name = name;
	_ease = ease;
	_offset = offset;
}

void Follow::load(){
	_transform = getComponent<Transform>();
}

void Follow::lateLoad(){
	Entity* target = 0;

	if (_name != "")
		target = EntityManager::getEntity(_name);
	else if (_id != -1)
		target = EntityManager::getEntity(_id);

	if (target){
		_transform->setPosition(target->getComponent<Transform>()->position());
		_transform->setRotation(target->getComponent<Transform>()->rotation());
	}

	_transform->localTranslate(_offset);
}

void Follow::lateUpdate(double dt){
	Entity* target = 0;

	if (_name != "")
		target = EntityManager::getEntity(_name);
	else if (_id != -1)
		target = EntityManager::getEntity(_id);

	if (target){
		glm::vec3 position = target->getComponent<Transform>()->position();
		glm::quat rotation = target->getComponent<Transform>()->rotation();
		
		position = glm::mix(_transform->position(), position, (float)(_ease * dt));
		rotation = glm::slerp(_transform->rotation(), rotation, (float)((_ease / 5.0) * dt));

		_transform->setPosition(position);
		_transform->setRotation(rotation);
	}

	_transform->localTranslate(_offset);
}

void Follow::setId(int id){
	_id = id;
}

void Follow::setName(std::string name){
	_name = name;
}

void Follow::setOffset(const glm::vec3& offset){
	_offset = offset;
}

void Follow::setEase(float ease){
	_ease = ease;
}