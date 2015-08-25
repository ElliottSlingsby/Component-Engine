#pragma once

#include <vector>
#include <stack>
#include <map>
#include "Entity\Entity.hpp"
#include <typeinfo>

#ifndef MAX_ENTS
#define MAX_ENTS 1024 //Size of initial vector
#endif

struct System{
	const type_info* type;

	System(const type_info* type) : type(type){}

	virtual void registerComponent(Component* component){}
	virtual void unregisterComponent(Component* component){}

	virtual void update(){};
	virtual ~System(){}
};

struct State{
	virtual void on(){}
	virtual void off(){}
	virtual ~State(){}
};

typedef std::vector<Entity*> EntityVector;

class EntityManager{
	// Collection of entities
	EntityVector _entities;
	// Removed ID pile
	std::stack<int> _removed;

	typedef std::vector<int> IntVector;
	typedef std::unordered_map<std::string, IntVector> EntityNameMap;
	EntityNameMap _names;

	typedef std::unordered_map<const type_info*, State*> StateMap;
	StateMap _states;

	typedef std::unordered_map<const type_info*, System*> SystemMap;
	SystemMap _systems;

	State* _currentState = 0;

	// Highest ID
	int _highest = 0;

	EntityManager();

	// Private singleton, used by static functions only
	static EntityManager& _instance();

	int _newID();
	void _removeID(int id);

public:
	~EntityManager();

	template<typename... T>
	static void invokeAll(void (Component::* method)(T...), T... args){
		for (int i = 0; i <= _instance()._highest; i++){
			Entity* entity = _instance()._entities[i];

			if (entity)
				entity->invoke(method, args...);
		}
	}

	template<typename T>
	static void addSystem(T* system){
		if (!_instance()._systems[&typeid(T)])
			_instance()._systems[&typeid(T)] = system;
		else
			printf("%s!\n", "System already added");
	}

	template<typename T>
	static void addState(T* state){
		if (!_instance()._states[&typeid(T)])
			_instance()._states[&typeid(T)] = state;
		else
			printf("%s!\n", "State already added");
	}

	template<typename T>
	static void changeState(){
		if (!_instance()._states[&typeid(T)])
			printf("%s!\n", "State doesn't exist");
		else if (_instance()._currentState == _instance()._states[&typeid(T)])
			printf("%s!\n", "State already on");
		else{
			if (_instance()._currentState)
				_instance()._currentState->off();

			_instance()._currentState = _instance()._states[&typeid(T)];
			_instance()._currentState->on();
		}
	}

	template<typename T = Entity, typename... U> 
	static Entity* createEntity(std::string name = "", U... args){
		// Pass any potential constructor args (if any)
		Entity* entity = new T(args...);

		// Make a new ID
		int id = _instance()._newID();

		if (_instance()._entities[id]){
			printf("%s: %s!\n", "Entity Manager", "New ID clashed with existing entity");
			_instance()._removeID(id);
			return 0;
		}

		if (name != ""){
			if (_instance()._names.find(name) == _instance()._names.end())
				_instance()._names[name] = IntVector();

			_instance()._names[name].push_back(id);
		}

		entity->setID(id);
		_instance()._entities[id] = entity;

		// Now that the ID has been set, it's safe to start adding components
		entity->prefab();
		
		return entity;
	}

	template<typename T>
	static void	registerToSystem(T* component){
		for (SystemMap::iterator i = _instance()._systems.begin(); i != _instance()._systems.end(); i++){
			if (i->second->type == &typeid(T))
				i->second->registerComponent(component);
		}
	}

	template<typename T>
	static void unregisterFromSystem(T* component){
		for (SystemMap::iterator i = _instance()._systems.begin(); i != _instance()._systems.end(); i++){
			if (i->second->type == &typeid(T))
				i->second->unregisterComponent(component);
		}
	}

	static void runSystems();

	static Entity* getEntity(int id);
	static Entity* getEntity(std::string name);
	static void getEntities(std::string name, EntityVector& results);

	static void destroyEntity(int id);
	static void destroyEntities(std::string name);
	static void destroyAll();

	static void deleteDestroyed();
};