#include "Entity.hpp"

#include "EntityManager.hpp"

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
	}
}

void Entity::load(bool enable){
	// Load all components if enabled
	for (ComponentMap::iterator i = _components.begin(); i != _components.end(); i++)
		i->second->load();

	if (enable)
		this->enable();
}

void Entity::enable(){
	// Enable all components if not enabled
	if (!_enabled){
		_enabled = true;

		for (ComponentMap::iterator i = _components.begin(); i != _components.end(); i++)
			i->second->enable();
	}
	else
		printf("%s!\n", "Entity already enabled");
}

void Entity::update(float dt){
	// Update all entites if enabled
	if (_enabled)
		for (ComponentMap::iterator i = _components.begin(); i != _components.end(); i++)
			i->second->update(dt);

	// Note: Should probably calculate dt inbetween updates aswell
}

void Entity::render(){
	// Render all components if enabled
	if (_enabled)
		for (ComponentMap::iterator i = _components.begin(); i != _components.end(); i++)
			i->second->render();
}