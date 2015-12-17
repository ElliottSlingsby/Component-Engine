#include <Setup.hpp>

#include "MathsDemo.hpp"

#include "CollisionSystem.hpp"

bool setup(int argc, char *args[]){
	Renderer::window().setSize(1280, 720);
	Renderer::window().setFixedMouse(true);

	AssetLoader::setAssetLocation("data/assets");
	Renderer::shaderManager().setShaderLocation("data/shaders");

	if (!Renderer::initiate())
		return false;

#ifdef _DEBUG
	Renderer::console().setRunning(true);
#endif

	EntityManager::systemHandler().addSystem(new CollisionSystem);
	
	EntityManager::stateMachine().addState(new MathsDemo);
	EntityManager::stateMachine().changeState<MathsDemo>();

	return true;
}