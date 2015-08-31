#include "Setup.hpp"

#include "State\Playing.hpp"
#include "State\Lost.hpp"
#include "State\Won.hpp"

void setup(int argc, char *args[]){
	Renderer::setWindowSize(1280, 720);

	AssetLoader::setAssetLocation("asset");

	EntityManager::addState(new Playing);
	EntityManager::addState(new Lost);
	EntityManager::addState(new Won);

	EntityManager::changeState<Playing>();

	Entity* entity = EntityManager::getEntity("enemy");

	if (entity)
		entity->getComponent<Face>()->setDifficulty(1.f);
}