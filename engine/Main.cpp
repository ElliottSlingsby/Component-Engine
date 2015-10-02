#include "Setup.hpp"

#include <Static\Renderer.hpp>
#include <Static\EntityManager.hpp>

#include <time.h>
#include <list>

void stress(int big){
	int x = 0;

	for (int i = 0; i <= big; i++)
		x *= i;
}

int main(int argc, char *args[]){
	srand((unsigned int)time(0));

	bool running = setup(argc, args);
	
	std::clock_t start;
	double difference = 0.0;
	
	const int sampleRange = 100;
	int rangeCounter = 0;

	typedef std::list<double> doubleList;
	doubleList times;

	double fps = 200;
	double maxFrame = (double)CLOCKS_PER_SEC / fps;

	while (running && Renderer::Window().running()){
		// Start timer and check for exit conditions
		start = std::clock();

		SDL_Event e;

		while (SDL_PollEvent(&e) != 0){
			if (e.type == SDL_QUIT){
				running = false;
			}
			else if (e.type == SDL_KEYDOWN){
				if (e.key.keysym.sym == SDLK_ESCAPE)
					running = false;
			}
		}

		// Invoke entities and systems
		EntityManager::SystemHandler().runSystems();

		EntityManager::invokeAll(&Component::update, difference);
		EntityManager::invokeAll(&Component::lateUpdate, difference);

		EntityManager::invokeAll(&Component::preRender);
		EntityManager::invokeAll(&Component::render);

		EntityManager::deleteDestroyed();

		// Update window and console
		Renderer::Window().flip();

		Renderer::Window().setTitle(std::to_string(1.0 / difference).c_str());

		if (Renderer::Console().interpretInput() == Module::Console::EXIT_CODE)
			running = false;
		
		// Delta time calculations and averaging
		difference = (double)(std::clock() - start) / (double)CLOCKS_PER_SEC;

		if (difference < maxFrame){
			double delay = maxFrame - difference;

			SDL_Delay(delay);

			difference += ((double)(std::clock() - start) / (double)CLOCKS_PER_SEC) - difference;
		}

		times.insert(times.begin(), difference);

		if (rangeCounter < sampleRange)
			rangeCounter += 1;
		else
			times.pop_back();

		double average = 0.0;

		for (doubleList::iterator i = times.begin(); i != times.end(); i++)
			average += *i;

		difference = average / times.size();
	}

	EntityManager::destroyAll();
	EntityManager::deleteDestroyed();

	return 0;
}