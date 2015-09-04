#include "Static\Renderer.hpp"
#include "Static\EntityManager.hpp"
#include "System\Collision.hpp"
#include <time.h>
#include <chrono>

#include "Setup.hpp"

int main(int argc, char *args[]){
	srand((unsigned int)time(0));

	Renderer::setWindowSize(1280, 720);
	Renderer::setWindowMode(WINDOW_WINDOWED);

	EntityManager::addSystem(new Collision);

	setup(argc, args);

	bool running = Renderer::initiate();

	if (running){
		//Renderer::setShaderLocation("source/Shader");
		//Renderer::loadShader(SHADER_VERTEX, "shader.vert");

		//Renderer::linkShaders();

		EntityManager::invokeAll(&Component::load);
		EntityManager::invokeAll(&Component::lateLoad);
	}

	// Used for calculating delta time

	auto start = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();

	while (running){
		std::chrono::duration<double> dt = end - start;

		start = std::chrono::high_resolution_clock::now();

		Renderer::setWindowTitle(("FPS : " + std::to_string((int)(1 / dt.count()))).c_str());

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

		EntityManager::invokeAll(&Component::update, dt.count());
		EntityManager::invokeAll(&Component::lateUpdate, dt.count());

		EntityManager::invokeAll(&Component::preRender);
		EntityManager::invokeAll(&Component::render);

		Renderer::swapBuffer();

		EntityManager::deleteDestroyed();

		end = std::chrono::high_resolution_clock::now();
	}

	EntityManager::destroyAll();

	return 0;
}