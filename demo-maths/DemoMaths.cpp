#include "DemoMaths.hpp"

#include <Static\Renderer.hpp>

#include <Component\Camera.hpp>
#include <Component\Debug\Grid.hpp>
#include <Component\Noclip.hpp>
#include <Component\Input.hpp>

#include "Box2d.hpp"
#include "Box3d.hpp"

void DemoMaths::on(){
	// Origin entity contains coloured grid plane on Z axis
	Entity* origin = EntityManager::createEntity("origin");
	origin->addComponent(new Grid(256, 16, 8, Grid::AxisZ));
	
	// Player entity contains the camera, movement controls, and a collider
	Entity* player = EntityManager::createEntity("player");
	player->getComponent<Transform>()->setPosition(glm::vec3(0, 0, -128));
	player->addComponent(new Camera);
	player->getComponent<Camera>()->set2d(false);
	player->getComponent<Camera>()->setFov(90);
	player->getComponent<Camera>()->setDrawDistance(1024 * 8);
	player->addComponent(new Input);
	player->addComponent(new Noclip(128.f, 0.1f));
	player->addComponent(new Box3d(512.f, 512.f, 512.f));

	// Other entity contains a collider
	Entity* other = EntityManager::createEntity("other");
	other->getComponent<Transform>()->setPosition(glm::vec3(0, 512, 0));
	other->getComponent<Transform>()->setRotation(glm::quat(glm::vec3(0, 0, glm::radians(45.f))));
	other->addComponent(new Box3d(512.f, 256.f, 256.f));
	
	// Load all entities and subsequent components
	EntityManager::invokeAll(Entity::TRIGGER_LOAD);
}

void DemoMaths::off(){
	EntityManager::destroyAll();
	EntityManager::deleteDestroyed();
}