#include "Playing.hpp"

#include <Static\Renderer.hpp>

#include <Component\Box2d.hpp>
#include <Component\Circle2d.hpp>
#include <Component\Camera.hpp>
#include <Component\Debug\Axis.hpp>
#include <Component\Debug\Grid.hpp>

#include <Utils.hpp>

#include "Movement.hpp"
#include "Velocity.hpp"
#include "Input.hpp"
#include "Brain.hpp"
#include "Feeder.hpp"

#include "Vision.hpp"

void Playing::on(){

	//Entity* vision = EntityManager::createEntity("vision");
	//vision->getComponent<Transform>()->setRotation(glm::quat(glm::vec3(0, 0, glm::radians(90.f))));
	//vision->addComponent(new Vision(glm::vec2(1024, 1024), glm::vec2(7, 7)));
	//
	//vision->trigger(Entity::TRIGGER_LOAD);
	//
	//
	//
	//Vision& test = *vision->getComponent<Vision>();
	//
	//test._clear();
	//
	//test._plot(0, 200, 0.5f);
	//
	//test._print();



	Entity* origin = EntityManager::createEntity("origin");
	origin->getComponent<Transform>()->setPosition(glm::vec3(0, 0, 1));
	origin->addComponent(new Grid(512, 128, 8, Grid::AxisZ));
	origin->addComponent(new Camera);
	origin->getComponent<Camera>()->set2d(true);
	origin->getComponent<Camera>()->setZoom(20.f);
	
	Entity* player = EntityManager::createEntity("player");
	player->getComponent<Transform>()->setRotation(glm::quat(glm::vec3(glm::radians(90.f), 0, 0)));
	player->addComponent(new Velocity(1.f));
	player->addComponent(new Input);
	player->addComponent(new Movement(25000.f, true));
	player->addComponent(new Axis(256.f, false));
	player->addComponent(new Circle2d(256.f));
	player->addComponent(new Feeder(2.f, 10.f, 100.f));
	player->addComponent(new Vision(glm::vec2(2046, 2046), glm::vec2(9, 9)));
	//player->addComponent(new Brain);


	for (int i = 0; i < 10; i++){
		Entity* computer = EntityManager::createEntity("computer");
		computer->getComponent<Transform>()->setRotation(glm::quat(glm::vec3(glm::radians(90.f), 0, glm::radians(randomRange(360, 1)))));
		computer->getComponent<Transform>()->setPosition(glm::vec3(randomRange(_width, _spread), randomRange(_height, _spread), 0));
		computer->addComponent(new Circle2d(256.f));
		computer->addComponent(new Velocity(1.f));
		computer->addComponent(new Movement(25000.f));
		computer->addComponent(new Axis(256.f, false));
		computer->addComponent(new Feeder(2.f, 10.f, 100.f));
		computer->addComponent(new Brain);
	}

	//for (int i = 0; i < 25; i++){
	//	Entity* food = EntityManager::createEntity("food");
	//	food->getComponent<Transform>()->setRotation(glm::quat(glm::vec3(glm::radians(90.f), 0, 0)));
	//	food->getComponent<Transform>()->setPosition(glm::vec3(_random(_width, _spread), _random(_height, _spread), 0));
	//	food->addComponent(new Circle2d(128.f));
	//}

	EntityManager::invokeAll(Entity::TRIGGER_LOAD);
}

void Playing::off(){
	EntityManager::destroyAll();
	EntityManager::deleteDestroyed();
}