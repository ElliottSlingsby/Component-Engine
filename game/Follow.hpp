#pragma once

#include <Entity\HelperComponent.hpp>
#include <string>

class Follow : public HelperComponent{
	Transform* _transform = 0;

	int _id = NULL_ID;
	std::string _name = "";

	glm::vec3 _offset;
	float _ease;

public:
	Follow(int id, float ease, const glm::vec3& offset = glm::vec3(0, 0, 0));
	Follow(std::string name, float ease, const glm::vec3& offset = glm::vec3(0, 0, 0));

	void load();
	void lateLoad();
	void lateUpdate(double dt);

	void setId(int id = NULL_ID);
	void setName(std::string name = "");
	void setOffset(const glm::vec3& offset = glm::vec3());
	void setEase(float ease);
};