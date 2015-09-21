#pragma once

#include <string>
#include <Static\DebugOutput.hpp>

// Base class for both Component and Entity classes

#define NULL_ID -1

class Identifier{
	int _id = NULL_ID;
	std::string _name;

public:
	virtual ~Identifier(){}

	void setID(int id){
		if (_id == NULL_ID)
			_id = id;
		else
			message_out("%s!\n", "ID already set");
	}

	int ID(){
		if (_id == NULL_ID)
			message_out("%s!\n", "ID hasn't been set");

		return _id;
	}
};