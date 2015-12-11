#include "Vision.hpp"

#include <Utils.hpp>


Vision::Vision(glm::vec2 size, glm::vec2 resolution){
	_size = size;
	_resolution = resolution;

	_array.resize((int)(resolution.x * resolution.x));
}

void Vision::_clear(){
	for (int i = 0; i < _resolution.x * _resolution.y; i++)
		_array[i] = 0.f;
}

void Vision::_plot(float x, float y, float value, bool overdraw){
	glm::vec3 world = glm::vec3(x, y, 0.f);
	glm::vec3 local = (world - _transform->position()) * glm::quat(glm::vec3(0.f, 0.f, glm::eulerAngles(_transform->rotation()).z));

	int newX = (int)changeRange(-(_size.x / 2.f), _size.x / 2.f, 0.f, (float)_resolution.x, local.x);
	int newY = (int)changeRange(_size.y / 2.f, -(_size.y / 2.f), 0.f, (float)_resolution.y, local.y);

	if ((newX < 0 || newX >= _resolution.x) && !overdraw)
		return;

	if ((newY < 0 || newY >= _resolution.y) && !overdraw)
		return;

	if (overdraw &&  newX < 0)
		newX = 0;
	else if (overdraw && newX >= _resolution.x)
		newX = _resolution.x - 1;

	if (overdraw && newY < 0)
		newY = 0;
	else if (overdraw && newY >= _resolution.y)
		newY = _resolution.y - 1;
	_array[(newY * _resolution.x) + newX] = value;

}

void Vision::load(){
	_transform = getComponent<Transform>();
	_feeder = getComponent<Feeder>();
}

void Vision::update(double dt){
	_clear();
	
	Vec3Vector otherThreats;
	Vec3Vector otherFood;

	glm::vec3 nearestFood = _feeder->nearestFood(otherFood);
	glm::vec3 nearestThreat = _feeder->nearestThreat(otherThreats);
	
	if (_feeder->eating())
		_plot(_transform->position().x, _transform->position().y, -1);

	if (_feeder->beingEaten())
		_plot(_transform->position().x, _transform->position().y, 1);

	for (glm::vec3 position : otherFood){
		_plot(position.x, position.y, -1.f);
	}

	for (glm::vec3 position : otherThreats){
		_plot(position.x, position.y, 1.f);
	}


	_plot(nearestFood.x, nearestFood.y, -1.f, true);

	_plot(nearestThreat.x, nearestThreat.y, 1.f, true);


	_print();
	message_out("\n\n\n\n\n\n\n\n");
}

unsigned int Vision::length(){
	return _resolution.x * _resolution.y;
}

void Vision::_print(){
	for (int y = 0; y < _resolution.y; y++){
		for (int x = 0; x < _resolution.x; x++){
			//message_out("%5.2f ", _array[_resolution.x * y + x]);
			message_out("%2d", (int)_array[(_resolution.x * y) + x]);
		}
		message_out("\n");
	}
}

void Vision::get(FloatVector& vector){
	vector.resize(_resolution.x * _resolution.y);
	vector.insert(vector.begin(), _array.begin(), _array.end());
}