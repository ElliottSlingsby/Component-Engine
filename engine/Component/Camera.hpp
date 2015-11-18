#pragma once

#include <Entity\HelperComponent.hpp>
#include <Component\Transform.hpp>

class Camera : public HelperComponent{
	Transform* _transform = 0;

	int _verticalPadding = 0;
	int _horizontalPadding = 0;

	float _fogDensity = 0.f;

	int _fov = 90;
	int _drawDistance = 16384;

	bool _2d = false;
	float _zoom = 1.f;

public:
	void load();
	void preRender();

	void reshape();

	void set2d(bool mode);
	void setZoom(float zoom);
	void setFogDensity(float fogDensity);
	void setVerticalPadding(unsigned int verticalPadding);
	void setHorizontalPadding(unsigned int horizontalPadding);
	void setFov(unsigned int fov);
	void setDrawDistance(unsigned int drawDistance);
};