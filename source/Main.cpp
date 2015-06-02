#include <stdio.h>

#include "Entity.hpp"
#include "Renderer.hpp"
#include "Vector3.hpp"
#include "Transform.hpp"
#include "Ticker.hpp"
#include "Draw.hpp"

#undef main

int main(int argc, char* argv[]){
	Entity* stub = new Entity;
	stub->setID(1);

	stub->addComponent(new Transform(5, 6));
	stub->addComponent(new Ticker);
	stub->addComponent(new Draw);

	Renderer* renderer = new Renderer();

	bool running = renderer->init();

	while (running){
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0){
			if (e.type == SDL_QUIT){
				running = false;
			}
		}

		stub->update(0);
		stub->render(renderer);

		renderer->swap();
	}

	delete stub;
	delete renderer;

	return 0;
}