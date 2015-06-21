#include "EntityManager.hpp"

EntityManager::EntityManager(){
	_entities.resize(MAX_ENTS);
}

EntityManager& EntityManager::_instance(){
	static EntityManager instance;
	return instance;
}

int EntityManager::_newID(){
	if (_removed.empty()){
		_highest++;
		return _highest;
	}

	int id = _removed.top();
	_removed.pop();
	return id;
}

void EntityManager::_removeID(unsigned int id){
	if (id == _highest){
		_highest--;
		return;
	}

	_removed.push(id);
}

void EntityManager::add(Entity* entity){
	if (entity->ID() == NULL_ID){
		int id = _instance()._newID();

		if (_instance()._entities[id]){
			printf("%s: %s!\n", "Entity Manager", "New ID clashed with existing entity");
			return;
		}

		entity->setID(id);
		_instance()._entities[id] = entity;

		return;
	}

	printf("%s: %s!\n", "Entity Manager", "Cannot add an entity that already has an ID");
}

Entity* EntityManager::get(unsigned int id){
	Entity* entity = _instance()._entities[id];

	if (!entity){
		printf("%s: %s!\n", "Entity Manager", "Entity doesn't exist");
		return 0;
	}

	return entity;
}

void EntityManager::destroy(unsigned int id){
	Entity* entity = _instance()._entities[id];

	if (!entity){
		printf("%s: %s!\n", "Entity Manager", "Cannot destroy entity that doesn't exist");
		return;
	}

	_instance()._removeID(id);
	_instance()._entities[id] = 0;
	delete entity;
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