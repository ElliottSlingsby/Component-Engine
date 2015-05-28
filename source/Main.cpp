#include <stdio.h>

#include "Entity.hpp"
#include "Glut.hpp"

class Transform : public Component{
public:
	int x;
	int y;

	Transform(int x, int y){
		this->x = x;
		this->y = y;
	}

	void init(){}
	void enable(){}
	void update(long dt){}
};

#undef main

int main(int argc, char* argv[]){
	printf("Hello World!\n");

	Entity stub;

	Transform* position = new Transform(5, 6);

	stub.addComponent(position);

	printf("Transform.x = %d\n", stub.getComponent<Transform>()->x);
	printf("Transform.y = %d\n", stub.getComponent<Transform>()->y);

	run();

	//getchar();
	return 0;
}