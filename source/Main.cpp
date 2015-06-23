#include "ResourceManager.hpp"
#include "EntityManager.hpp"

#include "Render\Window.hpp"

#include "Prefab\Stub.hpp"

//#undef main

int main(int argc, char** argv){
	Entity* entity = EntityManager::instantiate<Stub>(0.f, 0.f, -10.f);

	//entity->destroyComponent<Transform>();
	entity->destroyComponent<Movement>();

	Window window;

	bool running = window.init();
	
	EntityManager::loadAll();

	while (running){
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0){
			if (e.type == SDL_QUIT){
				running = false;
			}
		}

		EntityManager::updateAll();
		EntityManager::renderAll();

		window.swap();
	}
	
	return 0;
}