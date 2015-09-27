#pragma once

#include "Module\SystemHandler.hpp"
#include "Module\StateMachine.hpp"
#include "Module\NameBank.hpp"

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

	std::stack<int> _removed; // Removed id pile
	int _highest = 0; // Highest id

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
	static Module::NameBank& NameBank();

	static void triggerAll(Entity::Triggers type);

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

		// Make a new id
		int id = _instance()._newID();

		if (_instance()._entities[id]){
			message_out("%s: %s!\n", "Entity Manager", "New id clashed with existing entity");
			_instance()._removeID(id);
			return 0;
		}

		if (name != "")
			NameBank().bindName(id, name);

		entity->setID(id);
		_instance()._entities[id] = entity;

		// Now that the id has been set, it's safe to start adding components
		entity->prefab();
		
		return entity;
	}

	static void setMaxSize(unsigned int size);

	static Entity* getEntity(int id);
	static Entity* getEntity(const std::string& name, unsigned int i = 0);
	static void getEntities(const std::string& name, EntityVector& results);
	static void getEntities(IntVector& ids);

	static void destroyEntity(int id, bool recursive = true);
	static void destroyEntities(const std::string& name, bool recursive = true);
	static void destroyAll();

	static void deleteDestroyed();
};