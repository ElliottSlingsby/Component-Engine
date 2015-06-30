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

void Entity::input(SDL_Event& evnt){
	if (_enabled)
		for (ComponentMap::iterator i = _components.begin(); i != _components.end(); i++)
			i->second->input(evnt);
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