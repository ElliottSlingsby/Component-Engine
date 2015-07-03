#pragma once

#include <vector>
#include <stack>
#include "Base\Entity.hpp"

#define MAX_ENTS 1024 //Size of initial vector

class EntityManager{
	// Collection of entities
	std::vector<Entity*> _entities;
	// Removed ID pile
	std::stack<int> _removed;

	// Highest ID
	int _highest = 0;

	EntityManager();

	// Private singleton, used by static functions only.
	static EntityManager& _instance();

	int _newID();
	void _removeID(int id);

public:
	~EntityManager();

	template<typename T = Entity, typename... U> 
	static Entity* instantiate(U... args){
		// Pass any potential constructor args
		Entity* entity = new T(args...);

		// Make a new ID
		int id = _instance()._newID();

		if (_instance()._entities[id]){
			printf("%s: %s!\n", "Entity Manager", "New ID clashed with existing entity");
			_removeID(id);
			return 0;
		}

		entity->setID(id);

		_instance()._entities[id] = entity;

		// Now that the ID has been set, it's safe to start adding components
		entity->prefab();
		
		return entity;
	}

	// Old Entity controls. These will be heavily expanded on, like name and tag searching.
	static void add(Entity* entity);
	static Entity* get(int id);
	static void destroy(int id);

	static void loadAll();
	static void updateAll(float dt);
	static void renderAll();
	static void deleteAll();
};