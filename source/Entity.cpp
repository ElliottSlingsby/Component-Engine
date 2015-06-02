#include "Entity.hpp"

Entity::Entity(){

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
		component->enable();

		entity->_components[i->first] = component;
	}

	return entity;
}

void Entity::update(long dt){
	//Calculate and add dt between components
	for (ComponentMap::iterator i = _components.begin(); i != _components.end(); i++)
		i->second->update(dt);
}