#pragma once

#include "Component.hpp"
#include <Static\EntityManager.hpp>
#include <Static\DebugOutput.hpp>

// This helper class is for deriving components, so that the derived component can get other components from it's associated entity

struct HelperComponent : public Component{
	template <typename T>
	T* getComponent(){
		if (id() != NULL_ID)
			return EntityManager::getEntity(id())->getComponent<T>();

		message_out("%s: %s!\n", "HelperComponent", "Cannot get component, entity id hasn't been assigned");
		return 0;
	}

	template <typename T>
	void addComponent(T* component){
		if (id() != NULL_ID){
			EntityManager::getEntity(id())->addComponent(component);
			return;
		}

		message_out("%s: %s!\n", "HelperComponent", "Cannot add component, entity id hasn't been assigned");
	}

	template <typename T>
	void destroyComponent(){
		if (id() != NULL_ID){
			EntityManager::getEntity(id())->destroyComponent(component);
			return;
		}
		
		message_out("%s: %s!\n", "HelperComponent", "Cannot destroy component, entity id hasn't been assigned");
	}

	Entity* owner(){
		if (id() != NULL_ID)
			return EntityManager::getEntity(id());

		message_out("%s: %s!\n", "HelperComponent", "Cannot find component, entity id hasn't been assigned");
		return 0;
	}

	std::string name(){
		return EntityManager::NameBank().getName(id());
	}
};