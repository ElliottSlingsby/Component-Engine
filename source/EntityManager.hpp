#pragma once

#include <vector>
#include <stack>
#include <map>
#include "Entity\Entity.hpp"

#define MAX_ENTS 1024 //Size of initial vector

class EntityManager{
	// Collection of entities
	std::vector<Entity*> _entities;
	// Removed ID pile
	std::stack<int> _removed;

	std::unordered_map<std::string, int> _names;

	// Highest ID
	int _highest = 0;

	EntityManager();

	// Private singleton, used by static functions only
	static EntityManager& _instance();

	int _newID();
	void _removeID(int id);

public:
	~EntityManager();

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
				_instance()._names[name] = id;
			else
				printf("%s: %s!\n", "Entity Manager", "Name clashed with existing entity");
		}

		entity->setID(id);

		_instance()._entities[id] = entity;

		// Now that the ID has been set, it's safe to start adding components
		entity->prefab();
		
		return entity;
	}

	// Old Entity controls, these will be heavily expanded on, like name and tag searching
	static Entity* getEntity(int id);
	static Entity* getEntity(std::string name);

	static void deleteEntity(int id);
	static void deleteEntity(std::string name);

	static void loadAll();
	static void updateAll(float dt);
	static void renderAll();
	static void deleteAll();
};