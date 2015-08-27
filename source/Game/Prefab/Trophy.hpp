#pragma once

#include "Entity\Entity.hpp"
#include "Component\Model.hpp"

#include "..\Component\Spinner.hpp"

class Trophy : public Entity{
	std::string _mesh;
	std::string _material;

	float _speed;

public:
	Trophy(Vector3f spawn, std::string mesh, std::string material, float speed = 100.f){
		_transform->setPosition(spawn);
		_transform->setScale(Vector3f(0.1f, 0.1f, 0.1f));

		_mesh = mesh;
		_material = material;

		_speed = speed;
	}

	void prefab(){
		addComponent(new Model(_mesh, _material));
		addComponent(new Spinner(_speed));
	}
};