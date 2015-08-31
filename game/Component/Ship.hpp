#pragma once

#include <Entity\HelperComponent.hpp>
#include <Component\Transform.hpp>
#include "Component\Camera.hpp"
#include "Component\Light.hpp"

#include "State\Lost.hpp"

class Ship : public HelperComponent{
	Transform* _transform = 0;
	Entity* _camera = 0;

	float _ease(float value, float target, long double speed){
		return (float)(value + (target - value) * speed);
	}

public:
	void load(){
		_transform = getComponent<Transform>();
	}

	void lateLoad(){
		_camera = EntityManager::createEntity("ship");

		_camera->addComponent(new Camera);
		_camera->addComponent(new Light);
		_camera->getComponent<Transform>()->setPosition(_transform->position());
		_camera->getComponent<Transform>()->setRotation(_transform->rotation());
		_camera->getComponent<Transform>()->push(12.f, 90.f);
		_camera->getComponent<Transform>()->push(-40.f);

		_camera->invoke(&Component::load);
	}

	void lateUpdate(long double dt){
		Transform* camTransform = _camera->getComponent<Transform>();
	
		Vector3f camRotation = Vector3f(
			_ease(camTransform->rotation().x(), _transform->rotation().x(), 5 * dt),
			_ease(camTransform->rotation().y(), _transform->rotation().y(), 5 * dt),
			_ease(camTransform->rotation().z(), _transform->rotation().z(), 5 * dt)
		);

		camTransform->setPosition(_transform->position());
		camTransform->setRotation(camRotation);
		
		camTransform->push(12.f, 90.f);
		camTransform->push(-40.f);
	}


	void onCollision(int id){
		if (EntityManager::getEntity("sky") == EntityManager::getEntity(id)){
			EntityManager::changeState<Lost>();
		}
	}

	~Ship(){
		_camera->destroy();
	}
};