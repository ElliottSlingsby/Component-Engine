#pragma once

#include "Base\Entity.hpp"

#include "Component\Mesh.hpp"
#include "Component\Material.hpp"
#include "Component\Movement.hpp"

struct Example : public Entity{

	// Only the _transform component can be used in the constructor
	Example(float x = 0.f, float y = 0.f, float z = 0.f){
		_transform->setPosition(Vector3f(x, y, z));
	}

	// Other components can be setup and used by overriding prefab
	void prefab(){
		addComponent(new Material("regressiontest.jpg"));
		addComponent(new Mesh);
		addComponent(new Movement);
	}
};