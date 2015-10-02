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

#include "TestCamera.hpp"

void Playing::on(){
	Entity* sky = EntityManager::createEntity("sky");
	//sky->getComponent<Transform>()->setScale(glm::vec3(500, 500, 500));
	//sky->addComponent(new Model("relaxed_cube.obj", "grid.png"));
	//sky->getComponent<Model>()->setUnlit(true);
	
	Entity* player = EntityManager::createEntity("player");
	player->addComponent(new Velocity(1.f));
	player->addComponent(new Input(35000.f, 0.1f));

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

	//Entity* noclip = EntityManager::createEntity("noclip");
	//noclip->getComponent<Transform>()->setPosition(glm::vec3(0.f, 0.f, -100.f));
	//noclip->addComponent(new Camera);
	//noclip->addComponent(new Light);
	//noclip->addComponent(new Noclip(200.f, 0.2f));

	//EntityManager::createEntity<TestCamera>("noclip", glm::vec3(0.f, 0.f, -100.f), "player");

	sky->addComponent(new Axis(4096.f));
	sky->addComponent(new Grid(512, 64));
	player->addComponent(new Axis(10.f, false));
	camera->addComponent(new Axis(5.f, false));
	
	EntityManager::triggerAll(Entity::TRIGGER_LOAD);
}

void Playing::off(){
	EntityManager::destroyAll();
	EntityManager::deleteDestroyed();
}