#pragma once

#include <Entity\Entity.hpp>

class Sky : public Entity{
	float _size;

public:
	Sky(float size = 500.f);

	void prefab();
};