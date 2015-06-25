#pragma once

#include <vector>
#include <stack>
#include "Base\Entity.hpp"

#define MAX_ENTS 1024 //Size of initial vector

class EntityManager{
	std::vector<Entity*> _entities;
	std::stack<int> _removed;

	int _highest = 0;

	EntityManager();

	static EntityManager& _instance();

	int _newID();
	void _removeID(int id);

public:

	~EntityManager();

	template<typename T = Entity, typename... U> 
	static Entity* instantiate(U... args){
		Entity* entity = new T(args...);

		int id = _instance()._newID();

		if (_instance()._entities[id]){
			printf("%s: %s!\n", "Entity Manager", "New ID clashed with existing entity");
			return 0;
		}

		entity->setID(id);

		_instance()._entities[id] = entity;

		entity->prefab();
		
		return entity;
	}

	static void add(Entity* entity);
	static Entity* get(int id);
	static void destroy(int id);

	static void loadAll();
	static void updateAll();
	static void renderAll();
	static void deleteAll();
};