#include "Entity.hpp"

Entity::Entity(){
	_enabled = false;
}

Entity::~Entity(){
	// Destroy all components
	for (ComponentMap::iterator i = _components.begin(); i != _components.end(); i++){
		_components.erase(&typeid(i->second));
		delete i->second;
	}
}

Entity* Entity::clone(int id){
	Entity* entity = new Entity;
	entity->setID(id);

	// Clone components from this to clone
	for (ComponentMap::iterator i = _components.begin(); i != _components.end(); i++){
		Component* component = i->second->clone();

		component->setID(id);

		entity->_components[i->first] = component;
	}

	return entity;
}

void Entity::load(bool enable){
	for (ComponentMap::iterator i = _components.begin(); i != _components.end(); i++)
		i->second->load();

	if (enable)
		this->enable();
}

void Entity::enable(){
	if (!_enabled){
		_enabled = true;

		for (ComponentMap::iterator i = _components.begin(); i != _components.end(); i++)
			i->second->enable();
	}
	else
		printf("%s!\n", "Entity already enabled");
}

void Entity::update(long dt){
	//Calculate and add dt between components
	if (_enabled)
		for (ComponentMap::iterator i = _components.begin(); i != _components.end(); i++)
			i->second->update(dt);
}

void Entity::render(){
	if (_enabled)
		for (ComponentMap::iterator i = _components.begin(); i != _components.end(); i++)
			i->second->render();
}