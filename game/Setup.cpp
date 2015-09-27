#include <Setup.hpp>
#include <System\Collision.hpp>

#include "Playing.hpp"

#include <BulletCollision\CollisionShapes\btCapsuleShape.h>

bool setup(int argc, char *args[]){
	Renderer::Window().setSize(1280, 720);
	Renderer::Window().setFixedMouse(true);

	EntityManager::SystemHandler().addSystem(new Collision);

	AssetLoader::setAssetLocation("data/assets");
	Renderer::ShaderManager().setShaderLocation("data/shaders");

	if (!Renderer::initiate())
		return false;

	EntityManager::StateMachine().addState(new Playing);
	EntityManager::StateMachine().changeState<Playing>();

#ifdef _DEBUG
	Renderer::Console().setRunning(true);
#endif

	btCapsuleShape test(2.5, 10); // Testing bullet lib

	return true;
}