#include "Box.hpp"

#include "Sphere.hpp"

glm::vec3 Box::_min(){
	return _transform->position() - _offset;
}

glm::vec3 Box::_max(){
	return (_transform->position() + _size) - _offset;
}

Box::Box(const glm::vec3& size, bool inverted, const glm::vec3& offset) : Collider(COLLIDER_BOX, inverted){
	_offset = _offset;
}

bool Box::isColliding(Collider* other){
	Sphere* sphere = dynamic_cast<Sphere*>(other);

	if (sphere){
		return false;
	}

	Box* box = dynamic_cast<Box*>(other);

	if (box){
		return false;
	}

	return false;
}

void Box::setSize(const glm::vec3& size){
	_size = size;
}

void Box::setOffset(const glm::vec3& offset){
	_offset = offset;
}