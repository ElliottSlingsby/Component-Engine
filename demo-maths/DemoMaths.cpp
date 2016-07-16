#include "DemoMaths.hpp"

#include <Static\Renderer.hpp>

#include <Component\Camera.hpp>
#include <Component\Debug\Grid.hpp>
#include <Component\Noclip.hpp>
#include <Component\Input.hpp>
#include <Component\Debug\Spin.hpp>

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
	player->addComponent(new Box3d(256, 256, 256));

	// Other entity contains a collider
	Entity* box0 = EntityManager::createEntity("box");
	box0->getComponent<Transform>()->setPosition(glm::vec3(0, 512, 0));
	box0->getComponent<Transform>()->setRotation(glm::quat(glm::vec3(0, 0, glm::radians(45.f))));
	box0->addComponent(new Box3d(512.f, 256.f, 256.f));
	box0->addComponent(new Spin(1.f));

	Entity* box1 = EntityManager::createEntity("box");
	box1->getComponent<Transform>()->setPosition(glm::vec3(512, 512, 0));
	box1->getComponent<Transform>()->setRotation(glm::quat(glm::vec3(glm::radians(90.f), glm::radians(12.f), glm::radians(0.f))));
	box1->addComponent(new Box3d(512.f, 256.f, 256.f));
	box1->addComponent(new Spin(1.f));

	Entity* still = EntityManager::createEntity("still");
	still->getComponent<Transform>()->setPosition(glm::vec3(1024, -1024, 0));
	still->getComponent<Transform>()->setRotation(glm::quat(glm::vec3(glm::radians(90.f), 0.f, 0.f)));
	still->addComponent(new Box3d(512.f, 256.f, 256.f));

	Entity* spinner = EntityManager::createEntity("spinner");
	spinner->getComponent<Transform>()->setPosition(glm::vec3(-512, -512, 0));
	spinner->addComponent(new Box3d(1024, 128, 32));
	spinner->addComponent(new Spin(1.f));

	Entity* pillar0 = EntityManager::createEntity("pillar");
	pillar0->getComponent<Transform>()->setPosition(glm::vec3(-512 + 256, -512 + 256, 0));
	pillar0->addComponent(new Box3d(64, 64, 1024));
	pillar0->addComponent(new Spin(10.f));

	Entity* pillar1 = EntityManager::createEntity("pillar");
	pillar1->getComponent<Transform>()->setPosition(glm::vec3(-512 - 256, -512 - 256, 0));
	pillar1->addComponent(new Box3d(64, 64, 1024));
	pillar1->addComponent(new Spin(10.f));

	// Load all entities and subsequent components
	EntityManager::invokeAll(Entity::TRIGGER_LOAD);
}

void DemoMaths::off(){
	EntityManager::destroyAll();
	EntityManager::deleteDestroyed();
}