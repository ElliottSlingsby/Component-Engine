#include "Static\Renderer.hpp"
#include "Static\EntityManager.hpp"
#include "Setup.hpp"
#include <time.h>

int main(int argc, char** argv){
	srand((unsigned int)time(0));

	Renderer::setWindowSize(1280, 720);
	Renderer::setWindowMode(WINDOW_WINDOWED);
	
	// Used for calculating delta time
	int lastFrame = 0;
	int currFrame = 0;

	// Start running if renderer initiates successfully
	bool running = Renderer::initiate();

	if (running){
		setup();
		EntityManager::invokeAll(&Component::load);
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

		EntityManager::invokeAll(&Component::update, dt);
		EntityManager::invokeAll(&Component::render);
		
		Renderer::swapBuffer();
	}

	EntityManager::deleteAll();

	return 0;
}