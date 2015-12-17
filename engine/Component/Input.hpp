#pragma once

#include <Entity\HelperComponent.hpp>

#include <unordered_map>
#include <set>
#include <SDL.h>

class Input : public HelperComponent{
	typedef std::unordered_map<std::string, int> KeyMap;
	typedef std::set<std::string> StringSet;

	KeyMap _keybinds;

	StringSet _down;
	
public:
	Input();

	void update(double dt);

	bool isDown(const std::string& key);
};