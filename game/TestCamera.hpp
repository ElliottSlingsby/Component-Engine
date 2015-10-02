#pragma once

#include <Entity\Entity.hpp>

class TestCamera : public Entity{
	std::string _enableOnDelete;
	glm::vec3 _spawn;

public:
	TestCamera(const glm::vec3& spawn = glm::vec3(0, 0, 0), const std::string& enableOnDelete = "");
	~TestCamera();

	void prefab();
};