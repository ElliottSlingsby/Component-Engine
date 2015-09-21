#pragma once

#include "Module\SystemHandler.hpp"
#include "Module\StateMachine.hpp"

#include <vector>
#include <stack>
#include <unordered_map>
#include <Entity\Entity.hpp>
#include <typeinfo>
#include <Static\DebugOutput.hpp>

typedef std::vector<Entity*> EntityVector;

class EntityManager{
	// Collection of entities
	EntityVector _entities;
	
	typedef std::vector<int> IntVector;
	typedef std::unordered_map<std::string, IntVector> EntityNameIdMap;
	EntityNameIdMap _nameToIds;

	// Removed ID pile
	std::stack<int> _removed;

	// Highest ID
	int _highest = 0;

	EntityManager();

	// Private singleton, used by static functions only
	static EntityManager& _instance();

	int _newID();
	void _removeID(int id);

public:
	~EntityManager();

	// Modules
	static Module::SystemHandler& SystemHandler();
	static Module::StateMachine& StateMachine();

	template<typename... T>
	static void invokeAll(void (Component::* method)(T...), T... args){
		for (int i = 0; i <= _instance()._highest; i++){
			Entity* entity = _instance()._entities[i];
		
			if (entity)
				entity->invoke(method, args...);
		}
	}

	template<typename T = Entity, typename... U> 
	static Entity* createEntity(const std::string& name = "", U... args){
		// Pass any potential constructor args (if any)
		Entity* entity = new T(args...);

		// Make a new ID
		int id = _instance()._newID();

		if (_instance()._entities[id]){
			message_out("%s: %s!\n", "Entity Manager", "New ID clashed with existing entity");
			_instance()._removeID(id);
			return 0;
		}

		if (name != ""){
			if (_instance()._nameToIds.find(name) == _instance()._nameToIds.end())
				_instance()._nameToIds[name] = IntVector();

			_instance()._nameToIds[name].push_back(id);
		}

		entity->setID(id);
		_instance()._entities[id] = entity;

		// Now that the ID has been set, it's safe to start adding components
		entity->prefab();
		
		return entity;
	}

	static void setMaxSize(unsigned int size);

	static Entity* getEntity(int id);
	static Entity* getEntity(const std::string& name);
	static void getEntities(const std::string& name, EntityVector& results);

	static void destroyEntity(int id);
	static void destroyEntities(const std::string& name);
	static void destroyAll();

	static void deleteDestroyed();
};