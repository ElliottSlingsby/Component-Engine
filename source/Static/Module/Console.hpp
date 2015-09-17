#pragma once

#include <string>
#include <unordered_map>
#include <regex>

class Console{
	std::unordered_map<std::string, std::regex> _patternMap;
	std::string _prefix = "";

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
};