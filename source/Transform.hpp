#pragma once

#include "Component.hpp"
#include "Vector3.hpp"

struct Transform : public Component{
	Vector3f position;

	Transform(float x = 0.f, float y = 0.f, float z = 0.f){
		position = Vector3f(x, y, z);
	}

	Component* clone(){
		Transform* transform = new Transform();

		transform->position = position;

		return transform;
	}
};