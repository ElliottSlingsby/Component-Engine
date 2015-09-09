#include "Playing.hpp"
#include <Prefab\Player.hpp>
#include <Prefab\Sky.hpp>

void Playing::on(){
	EntityManager::createEntity<Sky>("sky");
	EntityManager::createEntity<Player>("player", glm::vec3(0.f, 0.f, -250.f));
}

void Playing::off(){
	EntityManager::destroyEntities("player");
	EntityManager::destroyEntities("sky");
}