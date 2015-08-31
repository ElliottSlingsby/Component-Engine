#pragma once

#include "Static\AssetLoader.hpp"
#include "Static\DebugPrint.hpp"
#include "Static\EntityManager.hpp"
#include "Static\Renderer.hpp"

void setup(int argc, char *args[]);

#ifdef _DEBUG
	#pragma comment(lib, "../lib/Engine-Debug.lib")
#else
	#pragma comment(lib, "../lib/Engine.lib")
#endif