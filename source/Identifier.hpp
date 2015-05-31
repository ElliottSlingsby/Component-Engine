#pragma once

#include <stdio.h>

class Identifier{
	int _id = -1;

public:
	void ID(int id){ 
		if (_id == -1){
			_id = id;
		}
		else{
			printf("%s!\n", "ID is already set");
		}
	}

	int ID(){
		if (_id == -1){
			printf("%s!\n", "ID hasn't been set");
		}

		return _id;
	}
};