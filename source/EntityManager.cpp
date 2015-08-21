#include "EntityManager.hpp"

EntityManager::EntityManager(){
	// Set initial vector size
	_entities.resize(MAX_ENTS);
}

EntityManager::~EntityManager(){
	// Purge!
	deleteAll();
}

EntityManager& EntityManager::_instance(){
	// Singleton implementation
	static EntityManager instance;
	return instance;
}

int EntityManager::_newID(){
	// If no removed IDs available
	if (_removed.empty()){
		// Create new one
		_highest++;
		return _highest - 1;
	}

	// Otherwise pop off used one
	int id = _removed.top();
	_removed.pop();

	return id;
}

void EntityManager::_removeID(int id){
	// If id was at the top
	if (id == _highest - 1){
		_highest--;
		return;
	}

	// Otherwise add it to the removed pile
	_removed.push(id);
}

Entity* EntityManager::getEntity(int id){
	Entity* entity = _instance()._entities[id];

	if (!entity){
		printf("%s: %s %d %s!\n", "Entity Manager", "Entity with ID", id, "doesn't exist!");
		return 0;
	}

	return entity;
}

Entity* EntityManager::getEntity(std::string name){
	if (!_instance()._names[name]){
		printf("%s: %s %s %s!\n", "Entity Manager", "Entity with name", name.c_str(), "doesn't exist!");
		return 0;
	}

	return getEntity(_instance()._names[name]);
}

void EntityManager::deleteEntity(int id){
	Entity* entity = _instance()._entities[id];

	if (!entity){
		printf("%s: %s %d %s!\n", "Entity Manager", "Entity with ID", id, "doesn't exist!");
		return;
	}

	std::unordered_map<std::string, int>::iterator i;

	for (i = _instance()._names.begin(); i != _instance()._names.end(); i++){
		if (i->second == id){
			std::string key = i->first;
			_instance()._names.erase(key);

			break;
		}
	}

	_instance()._removeID(id);
	_instance()._entities[id] = 0;
	delete entity;
}

void EntityManager::deleteEntity(std::string name){
	if (!_instance()._names[name]){
		printf("%s: %s %s %s!\n", "Entity Manager", "Entity with name", name, "doesn't exist!");
		return;
	}

	deleteEntity(_instance()._names[name]);
}

void EntityManager::loadAll(){
	for (int i = 0; i <= _instance()._highest; i++){
		Entity* entity = _instance()._entities[i];

		if (entity)
			entity->load();
	}
}

void EntityManager::updateAll(float dt){
	for (int i = 0; i <= _instance()._highest; i++){
		Entity* entity = _instance()._entities[i];

		if (entity)
			entity->update(dt);
	}
}

void EntityManager::renderAll(){
	for (int i = 0; i <= _instance()._highest; i++){
		Entity* entity = _instance()._entities[i];

		if (entity)
			entity->render();
	}
}

void EntityManager::deleteAll(){
	for (int i = 0; i <= _instance()._highest; i++){
		Entity* entity = _instance()._entities[i];

		if (entity)
			deleteEntity(i);
	}
}