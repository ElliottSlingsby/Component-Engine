#include "Transform.hpp"

Transform::Transform(const Vec3& position, const Quat& rotation, const Vec3& scale){
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
	for (TransformSet::iterator i = _children.begin(); i != _children.end(); i++)
		intVector.push_back((*i)->id());
}

void Transform::_addChild(Transform* child){
	_children.insert(child);
}

void Transform::_removeChild(Transform* child){
	_children.erase(child);
}

Vec3 Transform::position(){
	if (_parent)
		return _parent->position() + _parent->rotation() * _position;
	else
		return _position;
}

Quat Transform::rotation(){
	if (_parent)
		return _parent->rotation() * _rotation;
	else
		return _rotation;
}

Vec3 Transform::localPosition(){
	return _position;
}

Quat Transform::localRotation(){
	return _rotation;
}

Vec3 Transform::scale(){
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

void Transform::setPosition(const Vec3& vector){
	_position = vector;
}

void Transform::setRotation(const Quat& vector){
	_rotation = vector;
}

void Transform::setScale(const Vec3& scale){
	_scale = scale;
}

Vec3 Transform::apply(const Vec3& vector){
	return (_rotation * vector) - _position;
}

void Transform::translate(const Vec3& vector){
	_position += vector;
}

void Transform::rotate(Quat rotation){
	_rotation = rotation * this->rotation();
}

void Transform::localTranslate(const Vec3& translation){
	translate(_rotation *  translation);
}

void Transform::localRotate(const Quat& rotation){
	_rotation *= rotation;
}

void Transform::lookAt(const Vec3& position){
	// Not implemented

}

Vec3 Transform::lookingAt(){
	// Not implemented
	return Vec3();
}