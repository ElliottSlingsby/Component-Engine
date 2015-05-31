#include "EntityManager.hpp"

EntityManager::EntityManager(){

}

EntityManager::~EntityManager(){

}

EntityManager& EntityManager::instance(){
	static EntityManager instance;

	return instance;
}