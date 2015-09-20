#include "Playing.hpp"
#include <Prefab\Player.hpp>
#include <Prefab\Sky.hpp>
#include <Component\Camera.hpp>
#include <Component\Light.hpp>

void Playing::on(){
	Entity* sky = EntityManager::createEntity<Sky>("sky");

	Entity* player = EntityManager::createEntity<Player>("player", glm::vec3(0.f, 0.f, -250.f));

	Entity* camera = EntityManager::createEntity("camera");
	camera->getComponent<Transform>()->setPosition(glm::vec3(0.f, -10.f, -50.f));
	camera->getComponent<Transform>()->setParent(player->getComponent<Transform>());
	camera->addComponent(new Camera);
	camera->addComponent(new Light);
}

void Playing::off(){
	EntityManager::destroyAll();
}