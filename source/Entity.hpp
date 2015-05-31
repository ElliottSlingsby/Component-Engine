#pragma once

#include <stdio.h>
#include <typeinfo>
#include <unordered_map>
#include "Component.hpp"
#include "Identifier.hpp"

class Entity : public Identifier{
private:
	typedef std::unordered_map<const type_info*, Component*> ComponentMap;
	ComponentMap _components;

public:
	Entity(){}
	~Entity(){}

	template <typename T>
	void addComponent(T* component){
		if (!_components[&typeid(T)]){//DOESN'T ACTUALLY CHECK FOR EXISTANCE!!!
			_components[&typeid(T)] = component;
		}
		else{
			printf("%s!\n", "Component already exists");
		}
	}

	template <typename T>
	T* getComponent(){
		Component* component = _components[&typeid(T)];

		if (component){//DOESN'T ACTUALLY CHECK FOR EXISTANCE!!!
			T* casted = dynamic_cast<T*>(component);

			if (!casted){
				printf("%s!\n", "Failed to cast component");
			}

			return casted;
		}
		else{
			printf("%s!\n", "Cannot find component");
		}
		
		return 0;
	}

	template <typename T>
	T* removeComponent(){
		T* component = getComponent<T>();

		if (component){//DOESN'T ACTUALLY CHECK FOR EXISTANCE!!!
			_components[&typeid(T)] = 0;
		}
		else{
			printf("%s!\n", "Cannot find component");
		}

		return component;
	}

	template <typename T>
	void destroyComponent(){
		Component* component = _components[&typeid(T)];

		if (component){//DOESN'T ACTUALLY CHECK FOR EXISTANCE!!!
			_components.erase(&typeid(T));
			_components[&typeid(T)] = 0;
			delete component;
		}
		else{
			printf("%s!\n", "Cannot find component");
		}
	}

	Entity* clone(){
		Entity* entity = new Entity();

		for (ComponentMap::iterator i = _components.begin(); i != _components.end(); i++){
			entity->_components[i->first] = i->second->clone();
		}

		return entity;
	}
};