#pragma once

#include <Entity\HelperComponent.hpp>
#include <Component\Transform.hpp>

class Camera : public HelperComponent{
	Transform* _transform = 0;

public:
	void load();
	void preRender();
};