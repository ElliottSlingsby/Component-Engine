#include "Window.hpp"
#include "EntityManager.hpp"

void setupEnts();

int main(int argc, char** argv){
	Window::size(720, 720);
	Window::fullscreen(WINDOW_WINDOWED);
	Window::title("Component Game");
	
	bool running = Window::initiate();

	if (running)
		setupEnts();

	while (running){
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0){
			if (e.type == SDL_QUIT)
				running = false;
			
			else if(e.type == SDL_KEYDOWN)
				if (e.key.keysym.sym == SDLK_ESCAPE)
					running = false;
		}

		EntityManager::updateAll();
		EntityManager::renderAll();
		  
		Window::swapBuffer();
	}

	EntityManager::deleteAll();

	return 0;
}

#include "Component\Phong.hpp"
#include "Component\Mesh.hpp"
#include "Component\Movement.hpp"
#include "Component\Light.hpp"

void setupEnts(){
	Entity* texture = EntityManager::instantiate();

	texture->addComponent(new Phong("regressiontest.jpg"));
	texture->addComponent(new Mesh);
	texture->addComponent(new Movement);

	Entity* light = EntityManager::instantiate();

	light->getComponent<Transform>()->position(Vector3f(10.f, 0.f, 0.f));
	light->addComponent(new Movement);
	light->addComponent(new Light);

	EntityManager::loadAll();
}