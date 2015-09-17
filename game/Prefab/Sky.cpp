#include "Sky.hpp"

#include <Component\Model.hpp>
#include <Component\Sphere.hpp>

Sky::Sky(float size){
	_size = size;
	_transform->setScale(glm::vec3(_size, _size, _size));
}

void Sky::prefab(){
	addComponent(new Sphere(_size + 30.f, true));
	addComponent(new Model("relaxed_cube.obj", "grid.png"));
}