#include "Entity.hpp"

#include "Static\EntityManager.hpp"

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