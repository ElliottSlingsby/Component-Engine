#pragma once

#include "Component.hpp"
#include "Vector3.hpp"

struct Transform : public Component{
	Vector3f position;

	Transform(int x = 0, int y = 0, int z = 0){
		position = Vector3f(x, y, z);
	}

	Component* clone(){
		Transform* transform = new Transform();

		transform->position = position;

		return transform;
	}
};