#pragma once

#include "Base\Entity.hpp"

#include "Component\Mesh.hpp"
#include "Component\Phong.hpp"
#include "Component\Movement.hpp"

struct Stub : public Entity{
	Stub(float x = 0.f, float y = 0.f, float z = 0.f){
		_transform->position(Vector3f(x, y, z));
	}

	void prefab(){
		addComponent(new Phong("regressiontest.jpg"));
		addComponent(new Mesh);
		addComponent(new Movement);
	}
};