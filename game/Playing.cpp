#include "Playing.hpp"

#include <Component\Camera.hpp>
#include <Component\Light.hpp>
#include <Component\Model.hpp>
#include <Component\Camera.hpp>
#include <Component\Debug\Axis.hpp>
#include <Component\Debug\Noclip.hpp>
#include <Component\Debug\Grid.hpp>

#include <Component\Box2d.hpp>

#include "Follow.hpp"
#include "Input.hpp"
#include "Velocity.hpp"

void Playing::on(){
	bool _2d = true;

	Entity* origin = EntityManager::createEntity("origin");
	origin->addComponent(new Axis(4096.f));

	Entity* floor = EntityManager::createEntity("floor");
	floor->addComponent(new Grid(512, 8, 8, Grid::AxisZ));
	
	Entity* player = EntityManager::createEntity("player");
	player->addComponent(new Velocity(1.f));
	player->addComponent(new Input(35000.f, 0.1f));
	player->getComponent<Input>()->set2d(_2d);
	player->addComponent(new Axis(10.f, false));
	player->addComponent(new Camera);
	player->getComponent<Camera>()->set2d(_2d);
	player->addComponent(new Box2d(256, 128));
			
	EntityManager::invokeAll(Entity::TRIGGER_LOAD);
}

void Playing::off(){
	EntityManager::destroyAll();
	EntityManager::deleteDestroyed();
}