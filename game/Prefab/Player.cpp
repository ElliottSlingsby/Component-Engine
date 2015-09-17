#include "Player.hpp"

#include <Component\Model.hpp>
#include <Component\Input.hpp>
#include <Component\Camera.hpp>
#include <Component\Sphere.hpp>

Player::Player(const glm::vec3& spawn){
	_transform->setScale(glm::vec3(0.1f, 0.1f, 0.1f));
	_transform->setPosition(spawn);
}

void Player::prefab(){
	addComponent(new Input(100.f, 0.2f));
	addComponent(new Model("ship.obj", "ship.png"));
	addComponent(new Sphere(1.f));
	addComponent(new Camera);
}