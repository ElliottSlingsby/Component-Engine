#pragma once

#include "Base\Component.hpp"

#include "Math\Vector3.hpp"
#include <math.h>

// Move this to a static Maths Utils class!!
static float rad(float deg){
	return (float)(deg * (M_PI / 180));
}

static float deg(float rad){
	return (float)(rad * (180 / M_PI));
}


class Transform : public Component{
	Vector3f _position;
	Vector3f _rotation;
	Vector3f _size;

public:
	Transform(){
		_position = Vector3f(0.f, 0.f, 0.f);
		_rotation = Vector3f(0.f, 0.f, 0.f);
		_size = Vector3f(1.f, 1.f, 1.f);
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

	Vector3f size(){
		return _size;
	}

	void setPosition(Vector3f vector){
		_position = vector;
	}

	void setRotation(Vector3f vector){
		_rotation = vector;
	}

	void setSize(Vector3f size){
		_size = size;
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