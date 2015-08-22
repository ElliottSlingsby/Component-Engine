#pragma once

#include "Entity\Component.hpp"
#include "Math\Vector3.hpp"
#include "Math\MathUtils.hpp"

class Transform : public Component{
	Vector3f _position;
	Vector3f _rotation;
	Vector3f _scale;

public:
	Transform(){
		_position = Vector3f(0.f, 0.f, 0.f);
		_rotation = Vector3f(0.f, 0.f, 0.f);
		_scale = Vector3f(1.f, 1.f, 1.f);
	}

	Transform(Vector3f position, Vector3f rotation){
		_position = position;
		_rotation = rotation;
	}

	Vector3f position(){
		return _position;
	}

	Vector3f rotation(){
		return _rotation;
	}

	Vector3f scale(){
		return _scale;
	}

	void setPosition(Vector3f vector){
		_position = vector;
	}

	void setRotation(Vector3f vector){
		_rotation = vector;
	}

	void setScale(Vector3f scale){
		_scale = scale;
	}

	void translate(Vector3f vector){
		_position += vector;
	}

	Vector3f lookingAt(){
		return Vector3f(
			cos(_rotation.y()) * cos(_rotation.x()),
			sin(_rotation.y()) * cos(_rotation.x()),
			sin(_rotation.x())			
		);
	}

	void push(float speed){
		// Pushes the Transform along the _rotation's euler angles.
		
		// Somewhat temporary until the Quaternion class gets implemented

		float sinX = sin(MathUtils::radians(_rotation.x()));
		float cosX = cos(MathUtils::radians(_rotation.x()));
		float sinY = sin(MathUtils::radians((_rotation.y() - 180)));
		float cosY = cos(MathUtils::radians((_rotation.y() - 180)));

		float x = (-cosX * sinY) * -1;
		float y = sinX;
		float z = -cosX * cosY;

		_position += Vector3f(x * speed, y * speed, z * speed);
	}

	void rotate(Vector3f vector){
		_rotation += vector;
	}
};