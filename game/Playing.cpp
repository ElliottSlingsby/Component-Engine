#include "Playing.hpp"

#include <Static\Renderer.hpp>

#include <Component\Box2d.hpp>
#include <Component\Circle2d.hpp>
#include <Component\Camera.hpp>
#include <Component\Debug\Axis.hpp>
#include <Component\Debug\Grid.hpp>

#include "Movement.hpp"
#include "Velocity.hpp"
#include "Input.hpp"
#include "Brain.hpp"
#include "Feeder.hpp"

int random(int range, int spread){
	return (rand() % range * spread) - (range / 2) * spread;
}

void Playing::on(){
	srand((unsigned int)time(0));

	Entity* origin = EntityManager::createEntity("origin");
	origin->getComponent<Transform>()->setPosition(glm::vec3(0, 0, 1));
	origin->addComponent(new Grid(512, 128, 8, Grid::AxisZ));
	origin->addComponent(new Camera);
	origin->getComponent<Camera>()->set2d(true);
	origin->getComponent<Camera>()->setZoom(10.f);
	
	Entity* player = EntityManager::createEntity("player");
	player->getComponent<Transform>()->setRotation(glm::quat(glm::vec3(glm::radians(90.f), 0, 0)));
	player->addComponent(new Velocity(1.f));
	player->addComponent(new Input);
	player->addComponent(new Movement(25000.f, true));
	player->addComponent(new Axis(256.f, false));
	player->addComponent(new Circle2d(256.f));
	player->addComponent(new Feeder);

	for (int i = 0; i < 10; i++){
		int x = random(_width, _spread);
		int y = random(_height, _spread);

		float rotation = random(360, 1);

		Entity* computer = EntityManager::createEntity("computer");
		computer->getComponent<Transform>()->setRotation(glm::quat(glm::vec3(glm::radians(90.f), 0, glm::radians(rotation))));
		computer->getComponent<Transform>()->setPosition(glm::vec3(x, y, 0));
		computer->addComponent(new Circle2d(256.f));
		computer->addComponent(new Velocity(1.f));
		computer->addComponent(new Movement(25000.f));
		computer->addComponent(new Axis(256.f, false));
		computer->addComponent(new Brain);
		computer->addComponent(new Feeder);
	}

	for (int i = 0; i < 25; i++){
		int x = random(_width, _spread);
		int y = random(_height, _spread);

		Entity* food = EntityManager::createEntity("food");
		food->getComponent<Transform>()->setRotation(glm::quat(glm::vec3(glm::radians(90.f), 0, 0)));
		food->getComponent<Transform>()->setPosition(glm::vec3(x, y, 0));
		food->addComponent(new Circle2d(128.f));
	}

	EntityManager::invokeAll(Entity::TRIGGER_LOAD);
}

void Playing::off(){
	EntityManager::destroyAll();
	EntityManager::deleteDestroyed();
}