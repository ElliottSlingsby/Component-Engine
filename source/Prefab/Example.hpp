#pragma once

#include "Base\Entity.hpp"

#include "Component\Mesh.hpp"
#include "Component\Material.hpp"
#include "Component\Movement.hpp"

struct Example : public Entity{
	Example(float x = 0.f, float y = 0.f, float z = 0.f){
		_transform->position(Vector3f(x, y, z));
	}

	void prefab(){
		addComponent(new Material("regressiontest.jpg"));
		addComponent(new Mesh);
		addComponent(new Movement);
	}
};