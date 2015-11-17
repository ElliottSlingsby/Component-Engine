#include "Input.hpp"

Input::Input(){
	_keybinds.insert({
		{ "up", SDL_SCANCODE_UP },
		{ "down", SDL_SCANCODE_DOWN },
		{ "left", SDL_SCANCODE_LEFT },
		{ "right", SDL_SCANCODE_RIGHT },
		{ "w", SDL_SCANCODE_W },
		{ "s", SDL_SCANCODE_S },
		{ "a", SDL_SCANCODE_A },
		{ "d", SDL_SCANCODE_D },
		{ "z", SDL_SCANCODE_Z },
		{ "x", SDL_SCANCODE_X },
		{ "q", SDL_SCANCODE_Q },
		{ "e", SDL_SCANCODE_E },
		{ "ctrl", SDL_SCANCODE_LCTRL },
		{ "shift", SDL_SCANCODE_LSHIFT }
	});
}

void Input::update(double dt){
	const Uint8* keysDown = SDL_GetKeyboardState(0);

	for (KeyMap::iterator i = _keybinds.begin(); i != _keybinds.end(); i++){
		StringSet::iterator keyString = _down.find(i->first);

		if (keysDown[i->second]){
			if (keyString == _down.end())
				_down.insert(i->first);
		}
		else{
			if (keyString != _down.end())
				_down.erase(i->first);
		}
	}
}

bool Input::isDown(const std::string& key){
	StringSet::iterator keyString = _down.find(key);

	if (keyString == _down.end())
		return false;

	return true;
}