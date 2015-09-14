#pragma once

#include <Entity\Component.hpp>
#include <typeinfo>
#include <unordered_map>

struct System{
	const type_info* type;

	System(const type_info* type) : type(type){}

	virtual void registerComponent(Component* component){}
	virtual void unregisterComponent(Component* component){}

	virtual void update(){}

	virtual ~System(){}
};

namespace Module{
	class Systems{
		typedef std::unordered_map<const type_info*, System*> SystemMap;
		SystemMap _systems;

	public:
		template<typename T>
		void addSystem(T* system){
			if (!_systems[&typeid(T)])
				_systems[&typeid(T)] = system;
			else
				message_out("%s!\n", "System already added");
		}

		template<typename T>
		void registerToSystem(T* component){
			for (SystemMap::iterator i = _systems.begin(); i != _systems.end(); i++){
				if (i->second->type == &typeid(T))
					i->second->registerComponent(component);
			}
		}

		template<typename T>
		void unregisterFromSystem(T* component){
			for (SystemMap::iterator i = _systems.begin(); i != _systems.end(); i++){
				if (i->second->type == &typeid(T))
					i->second->unregisterComponent(component);
			}
		}

		void runSystems(){
			for (SystemMap::iterator i = _systems.begin(); i != _systems.end(); i++){
				i->second->update();
			}
		}
	};
}