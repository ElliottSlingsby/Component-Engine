#include "Setup.hpp"

#include <Static\Renderer.hpp>
#include <Static\EntityManager.hpp>
#include <System\Collision.hpp>

#include <chrono>
#include <list>

void stress(int big){
	int x = 0;
	
	for (int i = 0; i <= big; i++){
		x *= i;
	}
}

int main(int argc, char *args[]){
	srand((unsigned int)time(0));

	bool running = setup(argc, args);

#ifdef _DEBUG
	if (running)
		Renderer::Console().setRunning(true);
#endif
	
	auto start = std::chrono::high_resolution_clock::now().time_since_epoch();
	double difference = 0.0;
	
	const int sampleRange = 50;
	int rangeCounter = 0;

	typedef std::list<double> doubleList;
	doubleList times;

#ifndef _DEBUG
	while (running && Renderer::Window().running()){
#else
	while (running && Renderer::Window().running() && Renderer::Console().running()){
#endif
		start = std::chrono::high_resolution_clock::now().time_since_epoch();

		Renderer::Window().setTitle(std::to_string(difference).c_str());

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

		Renderer::Window().flip();

		EntityManager::deleteDestroyed();
		
		difference = (std::chrono::high_resolution_clock::now().time_since_epoch() - start).count() / 10000000.0;

		times.insert(times.begin(), difference);

		if (rangeCounter <= sampleRange)
			rangeCounter += 1;
		else
			times.pop_back();

		doubleList::iterator i;
		double average = 0.0;

		for (i = times.begin(); i != times.end(); i++){
			average += *i;
		}

		difference = average / times.size();

		//stress(10000000);

		//message_out("%G\n", difference);
	}

	EntityManager::destroyAll();

	return 0;
}