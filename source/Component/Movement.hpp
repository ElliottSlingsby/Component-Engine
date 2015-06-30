#pragma once

#include "Base\HelperComponent.hpp"

// Testing movement

class Movement : public HelperComponent{
public:
	Transform* transform = 0;

	void load(){
		transform = _getComponent<Transform>();
	}

	void update(long dt){
		transform->rotate(Vector3f(0.f, 1.f, 0.f));
	}

	Component* clone(){
		return new Movement;
	}
};
