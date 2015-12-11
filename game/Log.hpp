#pragma once

#include <fstream>
#include <string>

#include "Vision.hpp"

#ifndef LOG_PATH
#define LOG_PATH "../data/log.txt"
#endif

void startFile(int amount, int inputs, int outputs, bool clear = false){
	std::fstream file;

	

	if (!clear){
		file.open(LOG_PATH, std::ios::in | std::ios::out);

		std::string line;

		file >> line;

		file.seekp(0);
	}
	else{
		file.open(LOG_PATH, std::ios::trunc | std::ios::out);
	}

	file << amount << " " << inputs << " " << outputs << "\n";

	file.close();
}

std::string join(const FloatVector& vector){
	std::string joined = "";

	int i = 0;
	for (float value : vector){
		joined = joined + std::to_string(value);

		if (i != vector.size() - 1)
			joined = joined + " ";

		i++;
	}

	return joined;
}

void logFile(const FloatVector& input, const FloatVector& output){


	static int n = 0;

	n++;
	
	if (n == 1)
		startFile(n, input.size(), output.size(), true);
	else
		startFile(n, input.size(), output.size());


	std::ofstream file;

	file.open(LOG_PATH, std::ios::out | std::ios::app);

	if (file.is_open()){
		file << join(input) << "\n" << join(output) << "\n";

		file.close();
	}
	



}