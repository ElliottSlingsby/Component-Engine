#include <Setup.hpp>

#include "Playing.hpp"
#include <floatfann.h>
#include <fann_cpp.h>

bool setup(int argc, char *args[]){
	srand((unsigned int)time(0));

	Renderer::window().setSize(1280, 720);
	Renderer::window().setFixedMouse(true);

	AssetLoader::setAssetLocation("data/assets");
	Renderer::shaderManager().setShaderLocation("data/shaders");

	if (!Renderer::initiate())
		return false;

#ifdef _DEBUG
	Renderer::console().setRunning(true);
#endif

	EntityManager::stateMachine().addState(new Playing);

	EntityManager::stateMachine().getState<Playing>()->setTraining(false);
	EntityManager::stateMachine().getState<Playing>()->setOffline(true);
	EntityManager::stateMachine().getState<Playing>()->setResolution(glm::vec2(5, 5));
	EntityManager::stateMachine().getState<Playing>()->setSize(glm::vec2(2048, 2048));

	EntityManager::stateMachine().changeState<Playing>();
	
	return true;
}