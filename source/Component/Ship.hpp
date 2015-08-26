#pragma once

#include <Entity\HelperComponent.hpp>
#include <Component\Transform.hpp>
#include "Component\Camera.hpp"
#include "Component\Light.hpp"

class Ship : public HelperComponent{
	Transform* _transform = 0;
	Entity* _camera = 0;

	float _ease(float value, float target, float speed){
		return value + (target - value) * speed;
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
		_camera->getComponent<Transform>()->push(-3.f, 90.f);
		_camera->getComponent<Transform>()->push(-10.f);

		_camera->invoke(&Component::load);
	}

	void lateUpdate(){

		Transform* camTransform = _camera->getComponent<Transform>();

		Vector3f camPosition = camTransform->position();
		Vector3f camRotation = camTransform->rotation();
		
		camPosition = Vector3f(
			_ease(camPosition.x(), _transform->position().x(), 0.25f),
			_ease(camPosition.y(), _transform->position().y(), 0.25f),
			_ease(camPosition.z(), _transform->position().z(), 0.25f)
		);

		camRotation = Vector3f(
			_ease(camRotation.x(), _transform->rotation().x(), 0.05f),
			_ease(camRotation.y(), _transform->rotation().y(), 0.05f),
			_ease(camRotation.z(), _transform->rotation().z(), 0.05f)
		);

		camTransform->setPosition(camPosition);
		camTransform->setRotation(camRotation);
		
		_camera->getComponent<Transform>()->push(3.f, 90.f);
		_camera->getComponent<Transform>()->push(-10.f);
	}


	void onCollision(int id){
		if (EntityManager::getEntity("sky") == EntityManager::getEntity(id)){
			_camera->destroy();
			parent()->destroy();
		}
	}

	~Ship(){
		_camera->destroy();
	}
};