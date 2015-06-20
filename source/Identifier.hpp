#pragma once

#include <stdio.h>

#define NULL_ID -1

class Identifier{
	int _id = NULL_ID;

public:
	virtual void setID(int id){ 
		if (_id == NULL_ID)
			_id = id;
		else
			printf("%s!\n", "ID already set");
	}

	virtual int ID(){
		if (_id == NULL_ID)
			printf("%s!\n", "ID hasn't been set");

		return _id;
	}
};