#include "TestCamera.hpp"

#include <Component\Camera.hpp>
#include <Component\Light.hpp>
#include <Component\Debug\Noclip.hpp>
#include "Input.hpp"
#include "Velocity.hpp"

TestCamera::TestCamera(const glm::vec3& spawn, const std::string& enableOnDelete){
	_spawn = spawn;
	_enableOnDelete = enableOnDelete;
}

TestCamera::~TestCamera(){
	if (_enableOnDelete == "")
		return;
	
	Entity* entity = EntityManager::getEntity(_enableOnDelete);

	if (entity){
		Input* input = entity->getComponent<Input>();
		Velocity* velocity = entity->getComponent<Velocity>();
	
		//if (input)
		//	input->active = true;
		//
		//if (velocity)
		//	velocity->active = true;
	}
}

void TestCamera::prefab(){
	getComponent<Transform>()->setPosition(_spawn);
	addComponent(new Camera);
	addComponent(new Light);
	addComponent(new Noclip(200.f, 0.2f));

	if (_enableOnDelete == "")
		return;

	Entity* entity = EntityManager::getEntity(_enableOnDelete);

	if (entity){
		Input* input = entity->getComponent<Input>();
		Velocity* velocity = entity->getComponent<Velocity>();

		//if (input)
		//	input->active = false;
		//
		//if (velocity)
		//	velocity->active = false;
	}
}