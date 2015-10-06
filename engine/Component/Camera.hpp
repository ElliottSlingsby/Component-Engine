#pragma once

#include <Entity\HelperComponent.hpp>
#include <Component\Transform.hpp>

class Camera : public HelperComponent{
	Transform* _transform = 0;

	unsigned int _verticalPadding = 0;
	unsigned int _horizontalPadding = 0;

	float _fogDensity = 0.f;

	unsigned int _fov = 90;
	unsigned int _drawDistance = 16384;

public:
	void load();
	void preRender();

	void reshape();

	void setFogDensity(float fogDensity);
	void setVerticalPadding(unsigned int verticalPadding);
	void setHorizontalPadding(unsigned int horizontalPadding);
	void setFov(unsigned int fov);
	void setDrawDistance(unsigned int drawDistance);
};