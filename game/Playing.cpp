#include "Playing.hpp"

#include <Component\Camera.hpp>
#include <Component\Light.hpp>
#include <Component\Model.hpp>
#include <Component\Camera.hpp>
#include <Component\Debug\Axis.hpp>
#include <Component\Debug\Noclip.hpp>
#include <Component\Debug\Grid.hpp>

#include "Follow.hpp"
#include "Input.hpp"
#include "Velocity.hpp"

void Playing::on(){
	Entity* origin = EntityManager::createEntity("origin");
	origin->addComponent(new Axis(4096.f));

	Entity* floor = EntityManager::createEntity("floor");
	floor->addComponent(new Grid(512, 16));
	
	Entity* player = EntityManager::createEntity("player");
	player->addComponent(new Velocity(1.f));
	player->addComponent(new Input(35000.f, 0.1f));
	player->addComponent(new Axis(10.f, false));
	
	Entity* model = EntityManager::createEntity("model");
	model->getComponent<Transform>()->setParent(player->getComponent<Transform>());
	model->getComponent<Transform>()->setPosition(glm::vec3(0.f, 0.f, 1.f));
	model->getComponent<Transform>()->setScale(glm::vec3(0.1f, 0.1f, 0.1f));
	model->addComponent(new Model("ship.obj", "ship.png"));

	Entity* camera = EntityManager::createEntity("camera");
	camera->getComponent<Transform>()->setPosition(glm::vec3(0.f, -10.f, -50.f));
	camera->addComponent(new Follow(player->id(), 15.f, glm::vec3(0.f, -5.f, -50.f)));
	camera->addComponent(new Camera);
	camera->addComponent(new Light);
	camera->addComponent(new Axis(5.f, false));
		
	EntityManager::triggerAll(Entity::TRIGGER_LOAD);
}

void Playing::off(){
	EntityManager::destroyAll();
	EntityManager::deleteDestroyed();
}