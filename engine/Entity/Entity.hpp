#pragma once

#include <typeinfo>
#include <unordered_map>
#include <Component\Transform.hpp>
#include <Static\DebugOutput.hpp>

class Entity : public Identifier{
protected:
	typedef std::unordered_map<const type_info*, Component*> ComponentMap;
	ComponentMap _components;
	
	bool _enabled = false;
	bool _destroyed = false;
	bool _loaded = false;

	// Transform is here as to be edited by prefabs in their constructor if needed
	Transform* _transform = 0;

public:
	Entity();
	// Destroys all components
	virtual ~Entity();

	enum Triggers{
		TRIGGER_ENABLE,
		TRIGGER_LOAD,
		TRIGGER_DESTROY
	};

	// Called just before loading, as to be overridden for prefabs
	virtual void prefab(){};

	void setID(int id);

	void destroy(bool recursive = true, unsigned int delay = 0);
	void trigger(Triggers type);

	bool destroyed();
	bool loaded();
	bool enabled();

	Entity* getParent();
	Entity* getChild(unsigned int i = 0);
	Entity* getChild(std::string name, bool recursive = false);

	int componentSize();
	int childrenSize();

	template<typename... T>
	void invoke(void (Component::* method)(T...), T... args){
		if (_enabled && _loaded && !_destroyed){
			for (ComponentMap::iterator i = _components.begin(); i != _components.end(); i++)
				(i->second->*method)(args...);

			return;
		}
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
				component->setID(id());
		}
		else
			message_out("%s!\n", "Component already exists");
	}

	// getComponent<type>() - Returns corresponding component key as appropriate type
	template <typename T>
	T* getComponent(){
		ComponentMap::iterator component = _components.find(&typeid(T));

		// If component exists, cast to T and return
		if (component != _components.end()){
			T* casted = dynamic_cast<T*>(component->second);

			if (!casted)
				message_out("%s!\n", "Failed to cast component");

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
				message_out("%s!\n", "Cannot destroy Transform component");
				return;
			}
			_components.erase(&typeid(T));

			delete component->second;
			component->second = 0;
		}
		else
			message_out("%s!\n", "Cannot find component");
	}

	template <typename T>
	T* getComponentInChildren(unsigned int i = 0){
		// Not yet implemented
		return 0;
	}

	friend class EntityManager;
};