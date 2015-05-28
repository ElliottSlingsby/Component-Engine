#pragma once

#include <unordered_map>
#include <typeinfo>

class Component{
public:
	Component(){}
	virtual ~Component(){};
	
	virtual void init() = 0;
	virtual void enable() = 0;
	virtual void update(long dt) = 0;
};

typedef std::unordered_map<const type_info*, Component*> ComponentMap;

class Entity{
private:
	int _id;
	ComponentMap _components;

public:
	Entity(int id = -1){ _id = id; };
	~Entity(){};

	template <typename T>
	void addComponent(T* component){
		if (!_components[&typeid(T)]){
			_components[&typeid(T)] = component;
		}
	};

	template <typename T>
	T* getComponent(){
		Component* component = _components[&typeid(T)];

		if (component){
			return dynamic_cast<T*>(component);
		}
		
		return 0;
	};

	template <typename T>
	T* removeComponent(){
		T* component = getComponent<T>();

		if (component){
			_components[&typeid(T)] = 0;
		}

		return component;
	};

	template <typename T>
	void destroyComponent(){
		Component* component = _components[&typeid(T)];

		if (component){
			_components.erase(&typeid(T));
			_components[&typeid(T)] = 0;
			delete component;
		}
	}
};