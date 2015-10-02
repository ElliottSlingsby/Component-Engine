#pragma once

#include <Component\Model.hpp>

class Line : public Model{
	glm::vec3 _vector;

public:
	Line(const glm::vec3& vector);

	void setVector(const glm::vec3& vector);
	glm::vec3 vector();

	void draw();
};