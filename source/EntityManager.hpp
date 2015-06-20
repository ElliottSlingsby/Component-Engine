#pragma once

#include <vector>
#include <stack>
#include "Entity.hpp"

#define MAX_ENTS 1024

class EntityManager{
	std::vector<Entity*> _entities;
	std::stack<unsigned int> _removed;

	int _highest = 0;

	EntityManager();

	static EntityManager& _instance();

	int _newId();

	void _removeId(unsigned int id);

public:
	static void add(Entity* entity, bool transform = true);
	static Entity* get(unsigned int id);

	static void loadAll();
	static void updateAll();
	static void renderAll();
};