#include "Setup.hpp"

#include <Static\Renderer.hpp>
#include <Static\EntityManager.hpp>
#include <System\Collision.hpp>

#include <ctime>

int main(int argc, char *args[]){
	srand((unsigned int)time(0));

	EntityManager::SystemHandler().addSystem(new Collision);

	setup(argc, args);

	bool running = Renderer::initiate();

	if (running){
		EntityManager::invokeAll(&Component::load);
		EntityManager::invokeAll(&Component::lateLoad);

		Renderer::Window().startConsole();
	}

	double start = SDL_GetTicks();
	double end = start;

	double difference = 0.0;

	while (running && Renderer::Window().running()){
		start = SDL_GetTicks();

		Renderer::Window().setTitle(std::to_string(1.0 / difference).c_str());

		// Checking for exit conditions
		SDL_Event e;

		while (SDL_PollEvent(&e) != 0){
			if (e.type == SDL_QUIT)
				running = false;

			else if (e.type == SDL_KEYDOWN)
			if (e.key.keysym.sym == SDLK_ESCAPE)
				running = false;
		}

		EntityManager::SystemHandler().runSystems();

		EntityManager::invokeAll(&Component::update, difference);
		EntityManager::invokeAll(&Component::lateUpdate, difference);

		EntityManager::invokeAll(&Component::preRender);
		EntityManager::invokeAll(&Component::render);

		Renderer::Window().swapBuffer();

		EntityManager::deleteDestroyed();

		//int n = 0;
		//
		//for (int i = 0; i < 10000000; i++){
		//	n *= i;
		//}

		end = SDL_GetTicks();
		difference = (end - start) / 1000.0;
	}

	EntityManager::destroyAll();

	return 0;
}