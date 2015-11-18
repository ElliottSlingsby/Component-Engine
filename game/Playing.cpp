#include "Playing.hpp"

#include <Component\Box2d.hpp>
#include <Component\Camera.hpp>
#include <Component\Debug\Axis.hpp>
#include <Component\Debug\Grid.hpp>

#include "Movement.hpp"
#include "Velocity.hpp"
#include "Input.hpp"

void Playing::on(){
	bool _2d = true;

	Entity* origin = EntityManager::createEntity("main");
	origin->addComponent(new Grid(512, 8, 8, Grid::AxisZ));
	origin->addComponent(new Input);
	
	Entity* player = EntityManager::createEntity("player");
	player->getComponent<Transform>()->setPosition(glm::vec3(0, 0, -1024));
	player->addComponent(new Velocity(1.f));
	player->addComponent(new Movement(35000.f, 0.1f));
	player->getComponent<Movement>()->set2d(_2d);
	player->addComponent(new Camera);
	player->getComponent<Camera>()->set2d(_2d);
	player->addComponent(new Box2d(512, 32));
	
	Entity* box0 = EntityManager::createEntity("box0");
	box0->getComponent<Transform>()->setPosition(glm::vec3(512, 512, 0));
	box0->getComponent<Transform>()->setRotation(glm::quat(glm::vec3(0, 0, 85)));
	box0->addComponent(new Box2d(256, 128));

	EntityManager::invokeAll(Entity::TRIGGER_LOAD);
}

void Playing::off(){
	EntityManager::destroyAll();
	EntityManager::deleteDestroyed();
}