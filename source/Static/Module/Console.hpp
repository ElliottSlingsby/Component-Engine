#pragma once

#include <string>
#include <unordered_map>
#include <regex>
#include <SDL_thread.h>

namespace Module{
	class Console{
		std::unordered_map<std::string, std::regex> _patternMap;
		std::string _prefix = ">>>";

		bool _running = false;
		SDL_Thread* _thread = 0;

	public:
		Console();

		enum ReturnCodes{
			NULL_CODE,
			INVALID_CODE,
			VALID_CODE,
			EXIT_CODE
		};

		void setPrefix(const std::string& prefix);
		std::string getInput();
		int interpretInput(const std::string& input);

		void setRunning(bool running);
		bool running();
	};
}