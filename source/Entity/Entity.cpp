#include "Entity.hpp"

#include <Static\EntityManager.hpp>

static int destroyThread(void* data){
	Entity* entity = static_cast<Entity*>(data);

	// wait time

	return 0;
}

void Entity::destroy(bool recursive, unsigned int delay){
	if (recursive)
		for (int i = 0; i < childrenSize(); i++)
			EntityManager::destroyEntity(getChild(i)->id());

	if (delay == 0){
		_destroyed = true;
		return;
	}

	// Not yet implemented
	// SDL_Thread a delayed deletion
}

void Entity::trigger(Triggers type){
	if (type == TRIGGER_ENABLE && !_enabled){
		_enabled = true;
		invoke(&Component::enable);
	}
	else if (type == TRIGGER_LOAD && !_loaded && !_enabled){
		_loaded = true;
		trigger(TRIGGER_ENABLE);
		invoke(&Component::load);
	}
}

bool Entity::destroyed(){
	return _destroyed;
}

bool Entity::enabled(){
	return _enabled;
}

bool Entity::loaded(){
	return _loaded;
}

Entity::Entity(){
	_transform = new Transform;
	addComponent(_transform);
}

void Entity::setID(int id){
	Identifier::setID(id);
	_transform->setID(id);
}

Entity::~Entity(){
	// Destroy all components
	for (ComponentMap::iterator i = _components.begin(); i != _components.end(); i++){
		_components.erase(&typeid(i->second));

		delete i->second;
		i->second = 0;
	}
}

Entity* Entity::getParent(){
	if (!_transform){
		message_out("%s!\n", "Entity doesn't have a transform yet");
		return 0;
	}

	if (!_transform->parent())
		return 0;

	return EntityManager::getEntity(_transform->parent()->id());
}

Entity* Entity::getChild(unsigned int i){
	if (!_transform){
		message_out("%s!\n", "Entity doesn't have a transform yet");
		return 0;
	}

	if (i >= _transform->childrenSize()){
		message_out("%s!\n", "Child index out of range");
		return 0;
	}

	IntVector children;
	_transform->childrenIDs(children);

	return EntityManager::getEntity(children[i]);
}

int Entity::componentSize(){
	return _components.size();
}

int Entity::childrenSize(){
	if (!_transform){
		message_out("%s!\n", "Entity doesn't have a transform yet");
		return 0;
	}

	return _transform->childrenSize();
}

Entity* Entity::getChild(std::string name, bool recursive){
	// Not yet implemented
	return 0;
}