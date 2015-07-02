#pragma once

#include "Component.hpp"
#include "EntityManager.hpp"

class HelperComponent : public Component{
protected:
	template <typename T>
	T* _getComponent(){
		if (ID() != NULL_ID)
			return EntityManager::get(ID())->getComponent<T>();

		printf("%s: %s!\n", "HelperComponent", "Cannot get component, entity ID hasn't been assigned");
		return 0;
	}

	template <typename T>
	void _addComponent(T* component){
		if (ID() != NULL_ID){
			EntityManager::get(ID())->addComponent(component);
			return;
		}

		printf("%s: %s!\n", "HelperComponent", "Cannot add component, entity ID hasn't been assigned");
	}

	template <typename T>
	void _destroyComponent(){
		if (ID() != NULL_ID){
			EntityManager::get(ID())->destroyComponent(component);
			return;
		}
		
		printf("%s: %s!\n", "HelperComponent", "Cannot destroy component, entity ID hasn't been assigned");
	}
};

// Addexceptions for when components can't find other required components in the same entity.
// Example below...

/*struct Example : public HelperComponent{
	void load(){
		if (!_getComponent<Other>())
			throw invalid_components;
	}

	Component* clone(){
		return new Example;
	}
}*/