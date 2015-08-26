//#ifdef _DEBUG
//#define DEBUG_PRINT(string, ...) printf (string, __VA_ARGS__)
//#else
//#define DEBUG_PRINT(string, ...) (0)
//#endif

#include "Static\Renderer.hpp"
#include "Static\EntityManager.hpp"
#include "System\Collision.hpp"
#include "Setup.hpp"
#include <time.h>

int main(int argc, char *args[]){
	srand((unsigned int)time(0));

	//DEBUG_PRINT("%d", 1);

	// Used for calculating delta time
	int lastFrame = 0;
	int currFrame = 0;

	EntityManager::addSystem(new Collision);

	setup();

	bool running = Renderer::initiate();

	if (running){
		EntityManager::invokeAll(&Component::load);
		EntityManager::invokeAll(&Component::lateLoad);
	}

	while (running){
		// Update timers
		lastFrame = currFrame;
		currFrame = SDL_GetTicks();

		float dt = (float)(currFrame - lastFrame) / 1000.f;

		Renderer::setWindowTitle(("FPS : " + std::to_string((int)(1.f / dt))).c_str());

		// Checking for exit conditions
		SDL_Event e;

		while (SDL_PollEvent(&e) != 0){
			if (e.type == SDL_QUIT)
				running = false;

			else if (e.type == SDL_KEYDOWN)
				if (e.key.keysym.sym == SDLK_ESCAPE)
					running = false;
		}

		EntityManager::runSystems();

		EntityManager::invokeAll(&Component::update, dt);
		EntityManager::invokeAll(&Component::lateUpdate);

		EntityManager::invokeAll(&Component::render);
		
		Renderer::swapBuffer();

		EntityManager::deleteDestroyed();
	}

	EntityManager::destroyAll();

	return 0;
}