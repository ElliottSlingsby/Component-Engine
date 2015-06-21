#pragma once

#include <vector>
#include <stack>
#include "Entity.hpp"

#define MAX_ENTS 1024 //Size of initial vector
#define SIZE_STEP 512; //Size vector will be increased by on overflow

class EntityManager{
	std::vector<Entity*> _entities;
	std::stack<unsigned int> _removed;

	int _highest = 0;

	EntityManager();

	static EntityManager& _instance();

	int _newID();
	void _removeID(unsigned int id);

public:

	template<typename T = Entity, typename... U> 
	static Entity* instantiate(U... args){
		Entity* entity = new T(args...);

		int id = _instance()._newID();

		if (_instance()._entities[id])
			return 0;

		entity->setID(id);

		_instance()._entities[id] = entity;

		entity->prefab();
		
		return entity;
	}

	static void add(Entity* entity);
	static Entity* get(unsigned int id);
	static void destroy(unsigned int id);

	static void loadAll();
	static void updateAll();
	static void renderAll();
};