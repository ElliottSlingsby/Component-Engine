#include <stdio.h>

#include "Entity.hpp"
#include "Glut.hpp"
#include "Vector3.hpp"
#include "Transform.hpp"
#include "Ticker.hpp"

#undef main

class Test{

};

int main(int argc, char* argv[]){
	Entity* stub = new Entity;
	stub->setID(1);

	stub->addComponent(new Transform(5, 6));
	stub->addComponent(new Ticker);

	bool running = false;

	if (init()){
		running = true;

		while (running){
			SDL_Event e;
			while (SDL_PollEvent(&e) != 0){
				if (e.type == SDL_QUIT){
					running = false;
				}
			}


			stub->update(0);
			render();
		}
	}

	destroy();

	return 0;
}