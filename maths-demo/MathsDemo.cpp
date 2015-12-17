#include "MathsDemo.hpp"

#include <Static\Renderer.hpp>

#include <Component\Camera.hpp>
#include <Component\Debug\Grid.hpp>
#include <Component\Debug\Noclip.hpp>
#include <Component\Input.hpp>

void MathsDemo::on(){
	Entity* origin = EntityManager::createEntity("main");
	origin->addComponent(new Grid(512, 8, 8, Grid::AxisZ));
	
	Entity* player = EntityManager::createEntity("player");
	player->getComponent<Transform>()->setPosition(glm::vec3(0, -512, 0));
	player->addComponent(new Camera);
	player->getComponent<Camera>()->set2d(false);
	player->getComponent<Camera>()->setFov(90);
	player->getComponent<Camera>()->setDrawDistance(1024 * 8);
	player->addComponent(new Input);
	player->addComponent(new Noclip(64.f, 0.1f));
		
	EntityManager::invokeAll(Entity::TRIGGER_LOAD);
}

void MathsDemo::off(){
	EntityManager::destroyAll();
	EntityManager::deleteDestroyed();
}