#include <Setup.hpp>

#include "Playing.hpp"

bool setup(int argc, char *args[]){
	Renderer::window().setSize(1280, 720);
	Renderer::window().setFixedMouse(true);

	AssetLoader::setAssetLocation("data/assets");
	Renderer::shaderManager().setShaderLocation("data/shaders");

	if (!Renderer::initiate())
		return false;

	EntityManager::stateMachine().addState(new Playing);
	EntityManager::stateMachine().changeState<Playing>();

#ifdef _DEBUG
	Renderer::console().setRunning(true);
#endif
	
	return true;
}