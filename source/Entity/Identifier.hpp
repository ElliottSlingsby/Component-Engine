#pragma once

#include <stdio.h>
#include <Static\DebugPrint.hpp>

// This is the base class for both Component and Entity classes.
// This is so Components know what Entity they're attached to, and also so that the EntityManager can keep track of the entity.

#define NULL_ID -1

class Identifier{
	int _id = NULL_ID;

public:
	virtual void setID(int id){
		if (_id == NULL_ID)
			_id = id;
		else
			printd("%s!\n", "ID already set");
	}

	virtual int ID(){
		if (_id == NULL_ID)
			printd("%s!\n", "ID hasn't been set");

		return _id;
	}
};