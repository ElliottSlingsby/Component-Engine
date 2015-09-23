#include "Identifier.hpp"

#include <Static\DebugOutput.hpp>

void Identifier::setID(int id){
	if (_id == NULL_ID)
		_id = id;
	else
		message_out("%s!\n", "ID already set");
}

int Identifier::ID(){
	if (_id == NULL_ID)
		message_out("%s!\n", "ID hasn't been set");

	return _id;
}