#include "Setup.hpp"

#include <Static\Renderer.hpp>
#include <Static\EntityManager.hpp>

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
	
	std::chrono::high_resolution_clock::duration start;
	double difference = 0.0;
	
	const int sampleRange = 100;
	int rangeCounter = 0;

	typedef std::list<double> doubleList;
	doubleList times;

	while (running && Renderer::Window().running()){
		start = std::chrono::high_resolution_clock::now().time_since_epoch();

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

		Renderer::Window().setTitle(std::to_string(1.0 / difference).c_str());

		EntityManager::SystemHandler().runSystems();

		EntityManager::invokeAll(&Component::update, difference);
		EntityManager::invokeAll(&Component::lateUpdate, difference);

		EntityManager::invokeAll(&Component::preRender);
		EntityManager::invokeAll(&Component::render);

		Renderer::Window().flip();

		EntityManager::deleteDestroyed();

		if (Renderer::Console().interpretInput() == Module::Console::EXIT_CODE)
			running = false;
		
		difference = (std::chrono::high_resolution_clock::now().time_since_epoch() - start).count() / 10000000.0;	

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

	return 0;
}