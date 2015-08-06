#pragma once

#include "Component.hpp"
#include "EntityManager.hpp"

// This helper class is for deriving components, so that the derived component can get other components from it's associated entity.

class HelperComponent : public Component{
protected:
	// Perform as long as component has ID.
	// Otherwise printf error.

	template <typename T>
	T* _getComponent(){
		if (ID() != NULL_ID)
			return EntityManager::getEntity(ID())->getComponent<T>();

		printf("%s: %s!\n", "HelperComponent", "Cannot get component, entity ID hasn't been assigned");
		return 0;
	}

	template <typename T>
	void _addComponent(T* component){
		if (ID() != NULL_ID){
			EntityManager::getEntity(ID())->addComponent(component);
			return;
		}

		printf("%s: %s!\n", "HelperComponent", "Cannot add component, entity ID hasn't been assigned");
	}

	template <typename T>
	void _destroyComponent(){
		if (ID() != NULL_ID){
			EntityManager::getEntity(ID())->destroyComponent(component);
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