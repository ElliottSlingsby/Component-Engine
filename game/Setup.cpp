#include "Setup.hpp"

#include "State\Playing.hpp"

void setup(int argc, char *args[]){
	Renderer::setWindowSize(1280, 720);

	AssetLoader::setAssetLocation("asset");

	EntityManager::addState(new Playing);

	EntityManager::changeState<Playing>();
}