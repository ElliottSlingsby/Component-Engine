#include "Setup.hpp"

#include <State\Playing.hpp>
#include <System\Collision.hpp>

void setup(int argc, char *args[]){
	Renderer::Window().setSize(1280, 720);
	Renderer::Window().setFixedMouse(true);

	AssetLoader::setAssetLocation("asset");

	EntityManager::StateMachine().addState(new Playing);

	EntityManager::StateMachine().changeState<Playing>();
}