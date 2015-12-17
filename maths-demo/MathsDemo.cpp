#include "MathsDemo.hpp"

#include <Static\Renderer.hpp>

#include <Component\Camera.hpp>
#include <Component\Debug\Grid.hpp>
#include <Component\Debug\Noclip.hpp>
#include <Component\Input.hpp>

#include "Box2d.hpp"

void MathsDemo::on(){
	Entity* origin = EntityManager::createEntity("main");
	origin->addComponent(new Grid(512, 8, 8, Grid::AxisZ));
	
	Entity* player = EntityManager::createEntity("player");
	player->getComponent<Transform>()->setPosition(glm::vec3(0, 0, -128));
	player->addComponent(new Camera);
	player->getComponent<Camera>()->set2d(false);
	player->getComponent<Camera>()->setFov(90);
	player->getComponent<Camera>()->setDrawDistance(1024 * 8);
	player->addComponent(new Input);
	player->addComponent(new Noclip(64.f, 0.1f));
	player->addComponent(new Box2d(512.f, 256.f));

	Entity* other = EntityManager::createEntity("other");
	other->getComponent<Transform>()->setPosition(glm::vec3(0, 512, 0));
	other->getComponent<Transform>()->setRotation(glm::quat(glm::vec3(0, 0, glm::radians(45.f))));
	other->addComponent(new Box2d(512.f, 256.f));
		
	EntityManager::invokeAll(Entity::TRIGGER_LOAD);
}

void MathsDemo::off(){
	EntityManager::destroyAll();
	EntityManager::deleteDestroyed();
}