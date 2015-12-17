#include "Playing.hpp"

#include <Static\Renderer.hpp>

#include <Component\Box2d.hpp>
#include <Component\Camera.hpp>
#include <Component\Debug\Axis.hpp>
#include <Component\Debug\Grid.hpp>

#include "Movement.hpp"
#include "Velocity.hpp"
#include "Input.hpp"
#include "Spin.hpp"
#include "Noclip.hpp"

#include <glm\vec3.hpp>

void Playing::on(){
	Entity* origin = EntityManager::createEntity("main");
	origin->addComponent(new Grid(512, 8, 8, Grid::AxisZ));


	Entity* camera = EntityManager::createEntity("player");
	//camera->getComponent<Transform>()->setPosition(glm::vec3(0, 0, -256));
	//camera->getComponent<Transform>()->setRotation(glm::quat(glm::vec3(glm::radians(90.f), 0, 0)));
	camera->addComponent(new Camera);
	camera->getComponent<Camera>()->set2d(false);
	camera->getComponent<Camera>()->setFov(90);
	camera->getComponent<Camera>()->setDrawDistance(1024 * 8);
	camera->addComponent(new Input);
	camera->addComponent(new Noclip(64.f, 0.1f));


	Entity* player = EntityManager::createEntity("player");
	player->getComponent<Transform>()->setScale(glm::vec3(8, 8, 8));
	player->addComponent(new Velocity(1.f));
	//player->addComponent(new Input);
	//player->addComponent(new Movement(25000.f, 0.1f));
	player->addComponent(new Model("sphere.obj", "white.png"));
	//player->addComponent(new Box2d(32, 32));

	//camera->getComponent<Transform>()->setParent(player->getComponent<Transform>());



	
	//Entity* model = EntityManager::createEntity("model");
	//model->getComponent<Transform>()->setPosition(glm::vec3(0, 0, 0));
	//model->getComponent<Transform>()->setScale(glm::vec3(2, 2, 2));
	////model->getComponent<Transform>()->setRotation(glm::quat(glm::vec3(glm::radians(-90.f), 0, 0)));
	//model->addComponent(new Model("cube.obj", "white.png", "main"));
	//model->addComponent(new Spin(0.5f));
	

	int size = 1;
	float spread = 256.f;
	
	for (int y = -size; y <= size; y++){
		for (int x = -size; x <= size; x++){
			Entity* box0 = EntityManager::createEntity("box");
			box0->addComponent(new Model("bunny.obj", "wood.mtl", "main"));
			box0->getComponent<Transform>()->setScale(glm::vec3(5, 5, 5));
			box0->getComponent<Transform>()->setPosition(glm::vec3(x * spread, y * spread, 0));
			box0->addComponent(new Spin(0.5f));
		}
	}
	

	//Entity* box0 = EntityManager::createEntity("box");
	//box0->addComponent(new Model("cube.obj", "test.mtl", "main"));
	//box0->getComponent<Model>()->setUnlit(true);
	//box0->getComponent<Transform>()->setScale(glm::vec3(5, 5, 5));
	//box0->getComponent<Transform>()->setPosition(glm::vec3(0, 0, 100));
	//box0->addComponent(new Spin(0.5f));

	//player->getComponent<Transform>()->setParent(box0->getComponent<Transform>());

	EntityManager::invokeAll(Entity::TRIGGER_LOAD);
}

void Playing::off(){
	EntityManager::destroyAll();
	EntityManager::deleteDestroyed();
}