#include "Transform.hpp"

Transform::Transform(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale){
	_position = position;
	_rotation = rotation;
	_scale = scale;
}

Transform::~Transform(){
	if (_parent)
		_parent->_removeChild(this);

	TransformSet::iterator i = _children.begin();

	while (i != _children.end()){
		(*i)->setParent(0);
		i = _children.begin();
	}
}

Transform* Transform::parent(){
	return _parent;
}

unsigned int Transform::childrenSize(){
	return _children.size();
}

void Transform::childrenIDs(IntVector& intVector){
	for (TransformSet::iterator i = _children.begin(); i != _children.end(); i++){
		intVector.push_back((*i)->ID());
	}
}

void Transform::_addChild(Transform* child){
	_children.insert(child);
}

void Transform::_removeChild(Transform* child){
	_children.erase(child);
}

glm::vec3 Transform::position(){
	if (_parent)
		return _parent->position() + _parent->rotation() * _position;
	else
		return _position;
}

glm::quat Transform::rotation(){
	if (_parent)
		return _parent->rotation() * _rotation;
	else
		return _rotation;
}

glm::vec3 Transform::scale(){
	return _scale;
}

void Transform::setParent(Transform* parent){
	if (parent == _parent || parent == this)
		return;

	if (_parent)
		_parent->_removeChild(this);

	if (parent)
		parent->_addChild(this);

	if (!parent && _parent){
		_position = position();
		_rotation = rotation();
	}

	_parent = parent;
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

void Transform::lookAt(const glm::vec3& position){
	// Not implemented
	//glm::lookAt(_position, position, glm::ve)
}

glm::vec3 Transform::lookingAt(){
	// Not implemented
	return glm::vec3();
}