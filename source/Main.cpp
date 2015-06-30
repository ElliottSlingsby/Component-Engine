#include "Window.hpp"
#include "EntityManager.hpp"

void setupEnts();

int main(int argc, char** argv){
	Window::size(1280, 720);
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

			else if (e.type == SDL_KEYDOWN){
				EntityManager::inputAll(e);

				if (e.key.keysym.sym == SDLK_ESCAPE)
					running = false;
			}
			else if (e.type == SDL_KEYUP)
				EntityManager::inputAll(e);
		}

		EntityManager::updateAll(0);
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
#include "Component\Camera.hpp"
#include "Component\Input.hpp"

void setupEnts(){
	Entity* camera = EntityManager::instantiate();
	camera->addComponent(new Input);
	camera->addComponent(new Camera);
	camera->addComponent(new Light);

	Entity* texture = EntityManager::instantiate();

	texture->getComponent<Transform>()->position(Vector3f(0.f, 0.f, -5.f));
	texture->addComponent(new Phong("regressiontest.jpg"));
	texture->addComponent(new Mesh);
	texture->addComponent(new Movement);


	EntityManager::loadAll();
}