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
	else if (_id != NULL_ID)
		target = EntityManager::getEntity(_id);

	if (target){
		glm::vec3 position = target->getComponent<Transform>()->position();
		glm::quat rotation = target->getComponent<Transform>()->rotation();
		
		position = glm::mix(_transform->position(), position - _transform->rotation() * -_offset, (float)((_ease * 0.8) * dt));
		rotation = glm::slerp(_transform->rotation(), rotation, (float)((_ease * 0.15) * dt));

		_transform->setPosition(position);
		_transform->setRotation(rotation);
	}
}

void Follow::zoom(float difference){
	glm::vec3 ratio = glm::normalize(_offset);
	_offset += ratio * difference;
}

void Follow::setTarget(int id){
	_id = id;
	_name = "";
}

void Follow::setTarget(std::string name){
	_name = name;
	_id = NULL_ID;
}

void Follow::setOffset(const glm::vec3& offset){
	_offset = offset;
}

void Follow::setEase(float ease){
	_ease = ease;
}