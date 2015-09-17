#include "Transform.hpp"

Transform::Transform(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale){
	_position = position;
	_rotation = rotation;
	_scale = scale;
}

glm::vec3 Transform::position(){
	return _position;
}

glm::quat Transform::rotation(){
	return _rotation;
}

glm::vec3 Transform::scale(){
	return _scale;
}

void Transform::setPosition(const glm::vec3& vector){
	_position = vector;
}

void Transform::setRotation(const glm::quat& vector){
	_rotation = vector;
}

void Transform::setScale(const glm::vec3& scale){
	_scale = scale;
}

void Transform::lookAt(const glm::vec3& position){
	//glm::lookAt(_position, position, glm::ve)
}

glm::vec3 Transform::lookingAt(){
	return glm::vec3();
}

void Transform::translate(const glm::vec3& vector){
	_position += vector;
}

void Transform::rotate(const glm::quat& rotation){
	_rotation = rotation * _rotation;
}

void Transform::localTranslate(const glm::vec3& translation){
	translate(_rotation *  translation);
}

void Transform::localRotate(const glm::quat& rotation){
	_rotation *= rotation;
}