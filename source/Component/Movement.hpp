#pragma once

#include "Helper.hpp"

// Testing movement

class Movement : public HelperComponent{
public:
	Transform* transform = 0;

	void load(){
		transform = _getComponent<Transform>();
	}

	void update(long dt){
		transform->translate(Vector3f(0.f, 0.f, 0.02f));
		transform->transform(Vector3f(0.5f, 1.f, 2.f));
	}

	Component* clone(){
		return new Movement;
	}
};
