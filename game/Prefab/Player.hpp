#pragma once

#include <Entity\Entity.hpp>

struct Player : public Entity{
	Player(const glm::vec3& spawn = glm::vec3(0.f, -10.f, -75.f));

	void prefab();
};