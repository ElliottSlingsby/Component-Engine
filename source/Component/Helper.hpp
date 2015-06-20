#pragma once

#include "Base.hpp"
#include "EntityManager.hpp"

class HelperComponent : public Component{
protected:
	template <typename T>
	T* getComponent(){
		if (ID() != NULL_ID)
			return EntityManager::get(ID())->getComponent<T>();

		return 0;
	}

	template <typename T>
	void addComponent(T* component){
		if (ID() != NULL_ID)
			EntityManager::get(ID())->addComponent(component);
	}

	template <typename T>
	void destroyComponent(){
		if (ID() != NULL_ID)
			EntityManager::get(ID())->destroyComponent(component);
	}
};