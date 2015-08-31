#include "Static\EntityManager.hpp"

EntityManager::EntityManager(){
	// Set initial vector size
	_entities.resize(1024);
}

EntityManager::~EntityManager(){
	// Purge!
	destroyAll();
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
		printd("%s: %s %d %s!\n", "Entity Manager", "Entity with ID", id, "doesn't exist");
		return 0;
	}

	return entity;
}

Entity* EntityManager::getEntity(std::string name){
	EntityNameMap::iterator container = _instance()._names.find(name);

	if (container == _instance()._names.end() || container->second.size() == 0){
		printd("%s: %s %s %s!\n", "Entity Manager", "Entity with name", name.c_str(), "doesn't exist");
		return 0;
	}

	return getEntity(_instance()._names[name][0]);
}

void EntityManager::getEntities(std::string name, EntityVector& results){
	EntityNameMap::iterator container = _instance()._names.find(name);

	if (container == _instance()._names.end() || container->second.size() == 0){
		printd("%s: %s %s %s!\n", "Entity Manager", "Entity with name", name.c_str(), "doesn't exist");
		return;
	}

	for (IntVector::iterator i = container->second.begin(); i != container->second.end(); i++){
		results.push_back(getEntity(*i));
	}
}

void EntityManager::destroyEntity(int id){
	Entity* entity = _instance()._entities[id];

	if (!entity){
		printd("%s: %s %d %s!\n", "Entity Manager", "Entity with ID", id, "doesn't exist");
		return;
	}

	EntityNameMap::iterator x;

	for (x = _instance()._names.begin(); x != _instance()._names.end(); x++){
		if (x->second.size() != 0){
			for (IntVector::iterator y = x->second.begin(); y != x->second.end(); y++){
				if (*y = id){
					x->second.erase(y);
					break;
				}
			}
		}
	}

	entity->destroy();
}

void EntityManager::destroyEntities(std::string name){
	EntityNameMap::iterator container = _instance()._names.find(name);

	if (container == _instance()._names.end() || container->second.size() == 0){
		printd("%s: %s %s %s!\n", "Entity Manager", "Entity with name", name.c_str(), "doesn't exist");
		return;
	}

	for (IntVector::iterator i = container->second.begin(); i != container->second.end(); i++){
		_instance()._entities[*i]->destroy();
	}

	container->second.clear();
}

void EntityManager::destroyAll(){
	for (int i = 0; i <= _instance()._highest; i++){
		Entity* entity = _instance()._entities[i];

		if (entity)
			entity->destroy();
	}
}

void EntityManager::runSystems(){
	for (SystemMap::iterator i = _instance()._systems.begin(); i != _instance()._systems.end(); i++){
		i->second->update();
	}
}

void EntityManager::deleteDestroyed(){
	for (int i = 0; i <= _instance()._highest; i++){
		Entity* entity = _instance()._entities[i];

		if (entity && entity->destroyed()){
			_instance()._removeID(entity->ID());
			_instance()._entities[entity->ID()] = 0;
			delete entity;
		}
	}
}

void EntityManager::setMaxSize(unsigned int size){
	_instance()._entities.resize(size);
}