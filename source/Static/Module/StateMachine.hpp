#pragma once

#include <typeinfo>
#include <unordered_map>
#include <Static\DebugOutput.hpp>

struct State{
	virtual void on(){}
	virtual void off(){}
	virtual ~State(){}
};

namespace Module{
	class StateMachine{
		typedef std::unordered_map<const type_info*, State*> StateMap;
		StateMap _states;

		State* _currentState = 0;

	public:
		
		template<typename T>
		void addState(T* state){
			if (!_states[&typeid(T)])
				_states[&typeid(T)] = state;
			else
				message_out("%s!\n", "State already added");
		}

		template<typename T>
		void changeState(){
			if (!_states[&typeid(T)])
				message_out("%s!\n", "State doesn't exist");
			else if (_currentState == _states[&typeid(T)])
				message_out("%s!\n", "State already on");
			else{
				if (_currentState)
					_currentState->off();

				_currentState = _states[&typeid(T)];
				_currentState->on();
			}
		}
	};
}