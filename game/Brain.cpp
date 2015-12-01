#include "Brain.hpp"

void Brain::load(){
	_movement = getComponent<Movement>();
}

void Brain::update(double dt){
	if (rand() % 100 == 0)
		_mode = rand() % 4;

	if (_mode == 1)
		_movement->forward();
	else if (_mode == 2)
		_movement->left();
	else if (_mode == 3)
		_movement->right();
}