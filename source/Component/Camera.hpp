#pragma once

#include <Entity\HelperComponent.hpp>
#include <Component\Transform.hpp>
#include <GL\glew.h>
#include "Static\Renderer.hpp"
#include <Math\MathUtils.hpp>

class Camera : public HelperComponent{
	Transform* _transform = 0;

	bool _hasTarget = false;
	Vector3f _target;

public:
	void load(){
		_transform = getComponent<Transform>();
	}
	
	void lateUpdate(long double dt){
		if (_hasTarget)
			_transform->lookAt(_target);
	}
	
	void earlyRender(){
		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();

		glRotatef(_transform->rotation().x(), 1.f, 0.f, 0.f);
		glRotatef(_transform->rotation().y(), 0.f, 1.f, 0.f);
		glRotatef(_transform->rotation().z(), 0.f, 0.f, 1.f);

		glTranslatef(_transform->position().x(), _transform->position().y(), _transform->position().z());
	}

	void setTarget(Vector3f target){
		_hasTarget = true;
		_target = target;
	}

	void removeTarget(){
		_hasTarget = false;
	}
};