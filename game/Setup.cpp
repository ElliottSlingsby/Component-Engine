#include "Setup.hpp"

#include <State\Playing.hpp>
#include <System\Collision.hpp>

#include <Static\Module\NameBank.hpp> // Testings

void setup(int argc, char *args[]){
	Renderer::Window().setSize(1280, 720);
	Renderer::Window().setFixedMouse(true);

	AssetLoader::setAssetLocation("data");
	Renderer::ShaderManager().setShaderLocation("data");

	EntityManager::StateMachine().addState(new Playing);
	EntityManager::StateMachine().changeState<Playing>();

	// Testings
	Module::NameBank bank;

	bank.bindName(5, "name1");
	bank.bindName(3, "name2");
	bank.bindName(7, "name2");

	intVector ids;
	bank.getIds("name2", ids);

	std::string name = bank.getName(3);

	bank.unbindName(5, "name1");
	bank.unbindName(3, "name2");
	bank.unbindName(7, "name2");
}