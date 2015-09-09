#include "Setup.hpp"

#include <Static\Renderer.hpp>
#include <Static\EntityManager.hpp>
#include <System\Collision.hpp>
#include <chrono>

int main(int argc, char *args[]){
	srand((unsigned int)time(0));

	Renderer::setWindowSize(1280, 720);
	Renderer::setWindowMode(WINDOW_WINDOWED);

	EntityManager::Systems().addSystem(new Collision);

	setup(argc, args);

	bool running = Renderer::initiate();

	if (running){
		//Renderer::setShaderLocation("source/Shader");
		//Renderer::loadShader(SHADER_VERTEX, "shader.vert");

		//Renderer::linkShaders();

		EntityManager::invokeAll(&Component::load);
		EntityManager::invokeAll(&Component::lateLoad);
	}

	auto start = std::chrono::steady_clock::now();
	auto end = start;

	std::chrono::duration<double> difference = end - start;

	while (running){
		start = std::chrono::steady_clock::now();

		// Checking for exit conditions
		SDL_Event e;

		while (SDL_PollEvent(&e) != 0){
			if (e.type == SDL_QUIT)
				running = false;

			else if (e.type == SDL_KEYDOWN)
			if (e.key.keysym.sym == SDLK_ESCAPE)
				running = false;
		}

		EntityManager::Systems().runSystems();

		EntityManager::invokeAll(&Component::update, difference.count());
		EntityManager::invokeAll(&Component::lateUpdate, difference.count());

		EntityManager::invokeAll(&Component::preRender);
		EntityManager::invokeAll(&Component::render);

		Renderer::swapBuffer();

		EntityManager::deleteDestroyed();

		end = std::chrono::steady_clock::now();
		difference = end - start;
	}

	EntityManager::destroyAll();

	return 0;
}