#include "EntityManager.hpp"

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

SystemHandler& EntityManager::systemHandler(){
	static SystemHandler systems;
	return systems;
}

StateMachine& EntityManager::stateMachine(){
	static StateMachine states;
	return states;
}

NameBank& EntityManager::nameBank(){
	static NameBank names;
	return names;
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

	if (!entity)
		return 0;

	return entity;
}

Entity* EntityManager::getEntity(const std::string& name, unsigned int i){
	IntVector ids;
	NameBank().getIds(name, ids);

	if (i >= ids.size() || ids.size() == 0)
		return 0;

	return getEntity(ids[i]);
}

void EntityManager::getEntities(const std::string& name, EntityVector& results){
	IntVector ids;
	NameBank().getIds(name, ids);

	for (IntVector::iterator i = ids.begin(); i != ids.end(); i++){
		Entity* entity = getEntity(*i);

		if (!entity->destroyed())
			results.push_back(getEntity(*i));
	}
}

void EntityManager::destroyEntity(int id, bool recursive){
	Entity* entity = _instance()._entities[id];

	if (!entity){
		message_out("%s: %s %d %s!\n", "Entity Manager", "Entity with id", id, "doesn't exist");
		return;
	}

	std::string name = NameBank().getName(id);

	if (name != "")
		NameBank().unbindName(id, name);

	entity->destroy(recursive);
}

void EntityManager::destroyEntities(const std::string& name, bool recursive){
	IntVector ids;
	NameBank().getIds(name, ids);

	for (IntVector::iterator i = ids.begin(); i != ids.end(); i++){
		destroyEntity(*i, recursive);
	}
}

void EntityManager::getEntities(IntVector& results){
	for (int i = 0; i <= _instance()._highest; i++){
		Entity* entity = _instance()._entities[i];

		if (entity && !entity->destroyed())
			results.push_back(entity->id());
	}
}

void EntityManager::destroyAll(){
	IntVector ids;
	getEntities(ids);

	for (IntVector::iterator i = ids.begin(); i != ids.end(); i++){
		destroyEntity(*i, false);
	}
}

void EntityManager::invokeAll(Entity::Triggers type){
	IntVector ids;
	getEntities(ids);

	for (IntVector::iterator i = ids.begin(); i != ids.end(); i++)
		getEntity(*i)->trigger(type);

	if (type == Entity::TRIGGER_LOAD)
		for (IntVector::iterator i = ids.begin(); i != ids.end(); i++)
			getEntity(*i)->invoke(&Component::lateLoad);
}

void EntityManager::deleteDestroyed(){
	for (int i = 0; i <= _instance()._highest; i++){
		Entity* entity = _instance()._entities[i];

		if (entity && entity->destroyed()){
			_instance()._removeID(entity->id());
			_instance()._entities[entity->id()] = 0;
			delete entity;
			entity = 0;
		}
	}
}

void EntityManager::setMaxSize(unsigned int size){
	_instance()._entities.resize(size);
}