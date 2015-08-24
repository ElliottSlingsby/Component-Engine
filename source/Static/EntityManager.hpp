#pragma once

#include <vector>
#include <stack>
#include <map>
#include "Entity\Entity.hpp"

#ifndef MAX_ENTS
#define MAX_ENTS 1024 //Size of initial vector
#endif

typedef std::vector<Entity*> EntityVector;

class EntityManager{
	// Collection of entities
	EntityVector _entities;
	// Removed ID pile
	std::stack<int> _removed;

	typedef std::vector<int> IntVector;

	typedef std::unordered_map<std::string, IntVector> EntityNameMap;
	EntityNameMap _names;

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
				_instance()._names[name] = IntVector();

			_instance()._names[name].push_back(id);
		}

		entity->setID(id);

		_instance()._entities[id] = entity;

		// Now that the ID has been set, it's safe to start adding components
		entity->prefab();
		
		return entity;
	}

	static Entity* getEntity(int id);
	static Entity* getEntity(std::string name);
	static void getEntities(std::string name, EntityVector& results);
	static void deleteEntity(int id);
	static void deleteEntities(std::string name);

	static void loadAll();
	static void updateAll(float dt);
	static void renderAll();
	static void deleteAll();
};