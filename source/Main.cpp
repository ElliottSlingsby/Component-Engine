#include <stdio.h>

#include "Entity.hpp"
#include "Glut.hpp"
#include "Vector3.hpp"

class Transform : public Component{
public:
	int x;
	int y;

	Transform(int x, int y){
		this->x = x;
		this->y = y;
	}

	void enable(){}
	void update(long dt){}

	Component* clone(){
		return new Transform(x, y);
	}
};

void run(){
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

			update();
			render();
		}
	}
}

#undef main

int main(int argc, char* argv[]){
	printf("Hello World!\n");

	Entity* stub = new Entity();

	Transform* position = new Transform(5, 6);

	stub->addComponent(position);

	printf("Transform.x = %d\n", stub->getComponent<Transform>()->x);
	printf("Transform.y = %d\n", stub->getComponent<Transform>()->y);

	Entity* test = stub->clone();

	test->getComponent<Transform>()->x = 10;

	printf("Transform.x = %d\n", stub->getComponent<Transform>()->x);
	printf("Transform.x = %d\n", test->getComponent<Transform>()->x);

	//stub->getComponent<int>();

	run();

	return 0;
}