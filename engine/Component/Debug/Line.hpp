#pragma once

#include <Component\Model.hpp>

class Line : public Model{
	Vec3 _vector;

public:
	Line(const Vec3& vector);

	void setVector(const Vec3& vector);
	Vec3 vector();

	void draw();
};