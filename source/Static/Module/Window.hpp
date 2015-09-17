#pragma once

#include <SDL.h>
#include <string>

namespace Module{
	class Window{
		std::string _title = "";

		unsigned int _width;
		unsigned int _height;

		int _windowMode = SDL_WINDOW_SHOWN;

		bool _fixedMouse = false;

		SDL_Window* _window = 0;
		SDL_Renderer* _renderer = 0;

		bool _running = false;
		bool _glEnabled;

	public:
		Window(bool glEnabled = false);
		~Window();

		// Setters
		void setRunning(bool running);
		void setFixedMouse(bool fixedMouse);
		void setSize(unsigned int width, unsigned int height);
		void setTitle(const char* title);
		void setWindowMode(int windowMode);
		void setGlContext(SDL_GLContext context);

		bool initiate();
		void startConsole();

		// Getters
		bool running();
		int width();
		int height();
		SDL_Renderer* renderer();
		SDL_Window* window();

		void swapBuffer();
	};
}