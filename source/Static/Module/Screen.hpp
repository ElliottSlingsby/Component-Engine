#pragma once

#include <SDL.h>
#include <string>

namespace Module{
	class Screen{
		std::string _title = "";

		unsigned int _width;
		unsigned int _height;

		int _windowMode = SDL_WINDOW_SHOWN;

		bool _fixedMouse = false;

		SDL_Window* _window = 0;
		SDL_Renderer* _renderer = 0;
		SDL_GLContext _glContext = 0;

		bool _running = false;
		bool _glEnabled;

	public:
		Screen(bool glEnabled = false);
		~Screen();

		// Setters
		void setFixedMouse(bool fixedMouse);
		void setSize(unsigned int width, unsigned int height);
		void setTitle(const char* title);
		void setWindowMode(int windowMode);

		bool initiate();

		// Getters
		int width();
		int height();
		SDL_Renderer* renderer();
		SDL_GLContext glContext();

		void swapBuffer();
	};
}