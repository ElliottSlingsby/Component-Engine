#include "Render\Window.hpp"

#include "ResourceManager.hpp"
#include "EntityManager.hpp"

#include "Component\Mesh.hpp"
#include "Component\Phong.hpp"

#include "Component\Movement.hpp"

#undef main

int main(int argc, char** argv){
	Window window;

	bool running = window.init();

	if (running){
		Entity* stub = new Entity;

		EntityManager::add(stub);

		stub->addComponent(new Phong);
		stub->addComponent(new Mesh);

		stub->addComponent(new Movement);

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

		delete stub;
	
		return 0;
	}

	return 1;
}