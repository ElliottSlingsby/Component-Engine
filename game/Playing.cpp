#include "Playing.hpp"

#include <Component\Camera.hpp>
#include <Component\Light.hpp>
#include <Component\Model.hpp>
#include <Component\Camera.hpp>

#include "Follow.hpp"
#include "Input.hpp"
#include "Velocity.hpp"
#include "Axes.hpp"

void Playing::on(){
	Entity* sky = EntityManager::createEntity("sky");
	sky->getComponent<Transform>()->setScale(glm::vec3(500, 500, 500));
	sky->addComponent(new Model("relaxed_cube.obj", "grid.png"));
	sky->getComponent<Model>()->setUnlit(true);
	
	Entity* player = EntityManager::createEntity("player");
	player->addComponent(new Velocity(0.005f));
	player->addComponent(new Input(20000.f, 0.075f));

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

	//Entity* test = EntityManager::createEntity("test");
	//test->getComponent<Transform>()->setPosition(glm::vec3(0.f, 0.f, -100.f));
	//test->addComponent(new Camera);
	//test->addComponent(new Light);

	sky->addComponent(new Axes(4096.f));
	player->addComponent(new Axes(10.f, false));
	camera->addComponent(new Axes(5.f, false));
	
	EntityManager::triggerAll(Entity::TRIGGER_LOAD);
}

void Playing::off(){
	EntityManager::destroyAll();
}