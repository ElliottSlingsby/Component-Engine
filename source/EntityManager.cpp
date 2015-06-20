#include "EntityManager.hpp"

EntityManager::EntityManager(){
	_entities.resize(MAX_ENTS);
}

EntityManager& EntityManager::_instance(){
	static EntityManager instance;
	return instance;
}

int EntityManager::_newId(){
	if (_removed.empty()){
		_highest++;
		return _highest;
	}
	else{
		int id = _removed.top();
		_removed.pop();
		return id;
	}
}

void EntityManager::_removeId(unsigned int id){
	if (id == _highest){
		_highest--;
		return;
	}

	_removed.push(id);
}

void EntityManager::add(Entity* entity){
	int id = _instance()._newId();

	if (_instance()._entities[id])
		return;

	entity->setID(id);
	_instance()._entities[id] = entity;
}

Entity* EntityManager::get(unsigned int id){
	Entity* entity = _instance()._entities[id];

	if (!entity)
		return 0;

	return entity;
}

void EntityManager::loadAll(){
	for (int i = 0; i <= _instance()._highest; i++){
		Entity* entity = _instance()._entities[i];

		if (entity)
			entity->load();
	}
}

void EntityManager::updateAll(){
	for (int i = 0; i <= _instance()._highest; i++){
		Entity* entity = _instance()._entities[i];

		if (entity)
			entity->update(0);
	}
}

void EntityManager::renderAll(){
	for (int i = 0; i <= _instance()._highest; i++){
		Entity* entity = _instance()._entities[i];

		if (entity)
			entity->render();
	}
}