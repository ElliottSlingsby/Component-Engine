#include "Setup.hpp"

#include <State\Playing.hpp>
#include <System\Collision.hpp>

void setup(int argc, char *args[]){
	Renderer::setWindowSize(1280, 720);

	AssetLoader::setAssetLocation("asset");

	EntityManager::States().addState(new Playing);

	EntityManager::States().changeState<Playing>();
}