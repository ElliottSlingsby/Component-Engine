#include <Setup.hpp>

#include "MathsDemo.hpp"

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

	Renderer::shaderManager().useProgram("");
	
	EntityManager::stateMachine().addState(new MathsDemo);
	EntityManager::stateMachine().changeState<MathsDemo>();

	return true;
}