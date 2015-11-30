#include "Playing.hpp"

#include <Static\Renderer.hpp>

#include <Component\Box2d.hpp>
#include <Component\Camera.hpp>
#include <Component\Debug\Axis.hpp>
#include <Component\Debug\Grid.hpp>

#include "Movement.hpp"
#include "Velocity.hpp"
#include "Input.hpp"

void Playing::on(){
	Entity* origin = EntityManager::createEntity("main");
	origin->addComponent(new Grid(512, 32, 8, Grid::AxisZ));
	origin->addComponent(new Camera);
	origin->getComponent<Camera>()->set2d(true);
	origin->getComponent<Camera>()->setZoom(5.f);
	
	Entity* player = EntityManager::createEntity("player");
	player->getComponent<Transform>()->setRotation(glm::quat(glm::vec3(glm::radians(90.f), 0, 0)));
	player->addComponent(new Velocity(1.f));
	player->addComponent(new Input);
	player->addComponent(new Movement(25000.f));
	player->addComponent(new Axis(128.f, false));

	EntityManager::invokeAll(Entity::TRIGGER_LOAD);
}

void Playing::off(){
	EntityManager::destroyAll();
	EntityManager::deleteDestroyed();
}