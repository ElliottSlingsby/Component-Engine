#include "Entity.hpp"

#include "Component\Transform.hpp"
#include "Component\Mesh.hpp"
#include "Component\Phong.hpp"

#include "Render\Window.hpp"

#include "ResourceManager.hpp"

#undef main

int main(int argc, char** argv){
	Entity* stub = new Entity;
	stub->setID(1);

	stub->addComponent(new Transform);
	stub->addComponent(new Phong);
	stub->addComponent(new Mesh);

	stub->load();

	Window* window = new Window();

	bool running = window->init();

	while (running){
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0){
			if (e.type == SDL_QUIT){
				running = false;
			}
		}

		stub->update(0);
		stub->render();

		window->swap();
	}

	delete stub;
	delete window;

	return 0;
}