#include "Entity.hpp"

#include <Static\EntityManager.hpp>

static int destroyThread(void* data){
	Entity* entity = static_cast<Entity*>(data);

	// time

	return 0;
}

void Entity::destroy(bool recursive, unsigned int delay){
	if (recursive){
		for (int i = 0; i < childrenSize(); i++){
			getChild(i)->destroy(true);
		}
	}

	if (delay == 0){
		_destroyed = true;
		return;
	}

	// Not yet implemented
	// SDL_Thread a delayed deletion
}

bool Entity::destroyed(){
	return _destroyed;
}

void Entity::setEnable(bool enable){
	_enabled = enable;
}

bool Entity::enabled(){
	return _enabled;
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

	return EntityManager::getEntity(_transform->parent()->ID());
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