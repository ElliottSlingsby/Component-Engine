#include <Setup.hpp>
#include <System\Collision.hpp>

#include "Playing.hpp"

bool setup(int argc, char *args[]){
	Renderer::Window().setSize(1280, 720);
	Renderer::Window().setFixedMouse(true);

	EntityManager::SystemHandler().addSystem(new Collision);

	AssetLoader::setAssetLocation("data/assets");
	Renderer::ShaderManager().setShaderLocation("data/shaders");

	bool success = Renderer::initiate();

	if (success){
		EntityManager::StateMachine().addState(new Playing);
		EntityManager::StateMachine().changeState<Playing>();

		return true;
	}

	return false;
}