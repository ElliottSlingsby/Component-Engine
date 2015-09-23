#pragma once

#include <Entity\HelperComponent.hpp>

class Axis : public HelperComponent{
	Transform* _transform = 0;

	float _length;
	bool _local;

public:
	Axis(float length, bool local = false);
	
	void load();
	void render();
};