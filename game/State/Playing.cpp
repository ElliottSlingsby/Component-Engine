#include "Playing.hpp"
#include <Prefab\Player.hpp>
#include <Prefab\Sky.hpp>

void Playing::on(){
	Entity* sky = EntityManager::createEntity<Sky>("player_sky");
	sky->getComponent<Transform>()->setScale(glm::vec3(100, 100, 100));

	EntityManager::createEntity<Sky>("sky");

	Entity* player = EntityManager::createEntity<Player>("player", glm::vec3(0.f, 0.f, -250.f));

	sky->getComponent<Transform>()->setParent(player->getComponent<Transform>());
}

void Playing::off(){
	EntityManager::destroyAll();
}