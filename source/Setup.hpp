#pragma once

#include "Static\Renderer.hpp"

#include "Game\State\Playing.hpp"
#include "Game\State\Lost.hpp"
#include "Game\State\Won.hpp"

void setup(int argc, char *args[]){
	Renderer::setWindowSize(1280, 720);
	Renderer::setWindowMode(WINDOW_WINDOWED);

	EntityManager::addState(new Playing);
	EntityManager::addState(new Lost);
	EntityManager::addState(new Won);

	EntityManager::changeState<Playing>();

	Entity* entity = EntityManager::getEntity("enemy");

	if (entity)
		entity->getComponent<Face>()->setDifficulty(0.8f);
}