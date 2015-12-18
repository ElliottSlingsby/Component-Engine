#include "DemoGraphics.hpp"

#include <Static\Renderer.hpp>

#include <Component\Camera.hpp>
#include <Component\Debug\Grid.hpp>
#include <Component\Noclip.hpp>
#include <Component\Input.hpp>
#include <Component\Debug\Spin.hpp>

void DemoGraphics::on(){
	Entity* origin = EntityManager::createEntity("origin");
	origin->addComponent(new Grid(128, 32, 8, Grid::AxisZ));
	
	Entity* player = EntityManager::createEntity("player");
	player->getComponent<Transform>()->setPosition(Vec3(0, -512, -128));
	player->addComponent(new Camera);
	player->getComponent<Camera>()->set2d(false);
	player->getComponent<Camera>()->setFov(90);
	player->getComponent<Camera>()->setDrawDistance(1024 * 8);
	player->addComponent(new Input);
	player->addComponent(new Noclip(128.f, 0.1f));
		
	Entity* model = EntityManager::createEntity("model");
	model->getComponent<Transform>()->setScale(Vec3(5, 5, 5));
	model->getComponent<Transform>()->setPosition(Vec3(0.f, 0.f, -25.f));
	model->addComponent(new Model("bunny.obj", "wood.mtl", "main"));
	model->addComponent(new Spin(0.5f));

	// Load all entities and subsequent components
	EntityManager::invokeAll(Entity::TRIGGER_LOAD);
}

void DemoGraphics::off(){
	EntityManager::destroyAll();
	EntityManager::deleteDestroyed();
}