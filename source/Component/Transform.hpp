#pragma once

#include "Base\Component.hpp"

#include "Math\Vector3.hpp"
#include <math.h>

// Move this to a static Maths Utils class!!
static float rad(float deg){
	return (float)(deg * (M_PI / 180));
}

class Transform : public Component{
	Vector3f _position;
	Vector3f _rotation;

public:
	Transform(){
		_position = Vector3f(0.f, 0.f, 0.f);
		_rotation = Vector3f(0.f, 0.f, 0.f);
	}

	Transform(Vector3f position, Vector3f rotation){
		_position = position;
		_rotation = rotation;
	}

	Component* clone(){
		return new Transform;
	}

	Vector3f position(){
		return _position;
	}

	Vector3f rotation(){
		return _rotation;
	}

	Vector3f position(Vector3f vector){
		_position = vector;
		return _position;
	}

	Vector3f rotation(Vector3f vector){
		_rotation = vector;
		return _rotation;
	}

	void translate(Vector3f vector){
		_position += vector;
	}

	void push(float speed){
		// Pushes the Transform along the _rotation's euler angles.
		
		// Somewhat temporary until the Quaternion class gets implemented

		float sinX = sin(rad(_rotation.x()));
		float cosX = cos(rad(_rotation.x()));
		float sinY = sin(rad((_rotation.y() - 180)));
		float cosY = cos(rad((_rotation.y() - 180)));

		float x = (-cosX * sinY) * -1;
		float y = sinX;
		float z = -cosX * cosY;

		_position += Vector3f(x * speed, y * speed, z * speed);
	}

	void rotate(Vector3f vector){
		_rotation += vector;
	}
};