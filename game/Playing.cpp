#include "Playing.hpp"

#include <Component\Camera.hpp>
#include <Component\Light.hpp>
#include <Component\Model.hpp>
#include <Component\Camera.hpp>

#include "Follow.hpp"
#include "Input.hpp"
#include "Velocity.hpp"
#include "Axis.hpp"

void Playing::on(){
	Entity* sky = EntityManager::createEntity("sky");
	sky->getComponent<Transform>()->setScale(glm::vec3(500, 500, 500));
	sky->addComponent(new Model("relaxed_cube.obj", "grid.png"));
	sky->addComponent(new Axis(4096.f));
	
	Entity* player = EntityManager::createEntity("player");
	player->addComponent(new Velocity(0.01f));
	player->addComponent(new Input(200.f, 0.075f));
	player->addComponent(new Axis(10.f, true));

	Entity* model = EntityManager::createEntity("model");
	model->getComponent<Transform>()->setParent(player->getComponent<Transform>());
	model->getComponent<Transform>()->setPosition(glm::vec3(0.f, 0.f, 1.f));
	model->getComponent<Transform>()->setScale(glm::vec3(0.1f, 0.1f, 0.1f));
	model->addComponent(new Model("ship.obj", "ship.png"));

	Entity* camera = EntityManager::createEntity("camera");
	camera->getComponent<Transform>()->setPosition(glm::vec3(0.f, -10.f, -50.f));
	camera->addComponent(new Follow(player->ID(), 15.f, glm::vec3(0.f, -10.f, -50.f)));
	camera->addComponent(new Camera);
	camera->addComponent(new Light);
		
	EntityManager::invokeAll(&Component::load);
	EntityManager::invokeAll(&Component::lateLoad);
}

void Playing::off(){
	EntityManager::destroyAll();
	EntityManager::deleteDestroyed();
}