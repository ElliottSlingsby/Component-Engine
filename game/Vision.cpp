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

void Vision::_plot(float x, float y, float value){
	glm::vec3 world = glm::vec3(x, y, 0.f);
	glm::vec3 local = (world - _transform->position()) * glm::quat(glm::vec3(0.f, 0.f, glm::eulerAngles(_transform->rotation()).z));

	
	int newX = (int)changeRange(-(_size.x / 2.f), _size.x / 2.f, 0.f, (float)_resolution.x, local.x);
	int newY = (int)changeRange(_size.y / 2.f, -(_size.y / 2.f), 0.f, (float)_resolution.y, local.y);


	if (0 > newX || newX >= _resolution.x)
		return;

	if (0 > newY || newY >= _resolution.y)
		return;

	_array[(newY * _resolution.x) + newX] = value;

}

void Vision::load(){
	_transform = getComponent<Transform>();
	_feeder = getComponent<Feeder>();
}

void Vision::update(double dt){
	_clear();

	_plot(_transform->position().x, _transform->position().y, 1);
	

	EntityVector food;
	EntityManager::getEntities("food", food);

	EntityVector computers;
	EntityManager::getEntities("computer", computers);

	for (Entity* entity : food){
		glm::vec3 position = entity->getComponent<Transform>()->position();

		_plot(position.x, position.y, -1.f);
	}

	//for (Entity* entity : computers){
	//	glm::vec3 position = entity->getComponent<Transform>()->position() - _transform->position();
	//
	//	Feeder* feeder = entity->getComponent<Feeder>();
	//
	//	if (feeder->capacity() == 0)
	//		continue;
	//			
	//	if (feeder->capacity() > _feeder->capacity()){
	//		float value = changeRange(_feeder->capacity(), feeder->maxCapacity(), 0.f, 1.f, feeder->capacity());
	//
	//		_plot(position.x, position.y, value);
	//	}
	//	else if (feeder->capacity() < _feeder->capacity()){
	//		float value = changeRange(_feeder->capacity(), 0.f, -1.f, 0.f, feeder->capacity());
	//
	//		_plot(position.x, position.y, value);
	//	}
	//}

	_print();
	message_out("\n\n\n\n\n\n\n\n");
}

unsigned int Vision::length(){
	return _resolution.x * _resolution.y;
}

const float* Vision::begin(){
	return &_array[0];
}

void Vision::_print(){
	for (int y = 0; y < _resolution.y; y++){
		for (int x = 0; x < _resolution.x; x++){
			message_out("%2d ", (int)glm::round(_array[_resolution.x * y + x]));
		}
		message_out("\n");
	}
}