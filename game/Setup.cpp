#include "Setup.hpp"

#include "State\Playing.hpp"
#include "State\Lost.hpp"
#include "State\Won.hpp"

void setup(int argc, char *args[]){
	AssetLoader::setLocation("asset");

	EntityManager::addState(new Playing);
	EntityManager::addState(new Lost);
	EntityManager::addState(new Won);

	EntityManager::changeState<Playing>();

	Entity* entity = EntityManager::getEntity("enemy");

	if (entity)
		entity->getComponent<Face>()->setDifficulty(0.8f);
}