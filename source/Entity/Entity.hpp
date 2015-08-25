#pragma once

#include <stdio.h>
#include <typeinfo>
#include <unordered_map>
#include "Component\Transform.hpp"

class Entity : public Identifier{
protected:
	typedef std::unordered_map<const type_info*, Component*> ComponentMap;
	ComponentMap _components;
	
	bool _enabled = false;
	bool _destroyed = false;

	// Transform is here as to be edited by prefabs in their constructor if needed
	Transform* _transform = 0;

public:
	Entity();
	// Destroys all components
	~Entity();

	// Called just before loading, as to be overridden for prefabs
	virtual void prefab(){};

	void setID(int id);

	void destroy();
	bool destroyed();

	template<typename... T>
	void invoke(void (Component::* method)(T...), T... args){
		for (ComponentMap::iterator i = _components.begin(); i != _components.end(); i++)
			(i->second->*method)(args...);

		if (typeid(method) == typeid((&Component::enable)))
			_enabled = true;
		else if (typeid(method) == typeid((&Component::load)))
			invoke(&Component::enable);
	}

	// addComponent(component) - Adds a component using typeid as key
	template <typename T>
	void addComponent(T* component){
		// Add component if not already part of Entity
		if (!_components[&typeid(T)]){
			// Parent and enable the component
			_components[&typeid(T)] = component;

			// Make an exception for Transform
			if (typeid(T) != typeid(Transform))
				component->setID(ID());
		}
		else
			printf("%s!\n", "Component already exists");
	}

	// getComponent<type>() - Returns corresponding component key as appropriate type
	template <typename T>
	T* getComponent(){
		ComponentMap::iterator component = _components.find(&typeid(T));

		// If component exists, cast to T and return
		if (component != _components.end()){
			T* casted = dynamic_cast<T*>(component->second);

			if (!casted)
				printf("%s!\n", "Failed to cast component");

			return casted;
		}

		return 0;
	}

	// destroyComponent<type>() - Removes and deletes component
	template <typename T>
	void destroyComponent(){
		ComponentMap::iterator component = _components.find(&typeid(T));

		// If component exists, erase and delete
		if (component != _components.end()){
			if (typeid(T) == typeid(Transform)){
				printf("%s!\n", "Cannot destroy Transform component");
				return;
			}

			delete component->second;
			_components.erase(&typeid(T));
		}
		else
			printf("%s!\n", "Cannot find component");
	}
};