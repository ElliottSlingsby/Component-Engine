#include "ResourceManager.hpp"
#include "EntityManager.hpp"

#include "Render\Window.hpp"

#include "Prefab\Stub.hpp"

int main(int argc, char** argv){
	Entity* entity = EntityManager::instantiate();

	entity->addComponent(new Phong("regressiontest.jpg"));
	entity->addComponent(new Mesh);
	entity->addComponent(new Movement);

	Window window;

	bool running = window.init();
	
	EntityManager::loadAll();

	while (running){
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
			if (e.type == SDL_QUIT)
				running = false;

		EntityManager::updateAll();
		EntityManager::renderAll();

		window.swap();
	}
	
	return 0;
}