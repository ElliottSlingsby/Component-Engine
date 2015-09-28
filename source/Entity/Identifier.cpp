#include "Identifier.hpp"

#include <Static\DebugOutput.hpp>

void Identifier::setID(int id){
	if (_id == NULL_ID)
		_id = id;
	else
		message_out("%s!\n", "id already set");
}

int Identifier::id(){
	if (_id == NULL_ID)
		message_out("%s!\n", "id hasn't been set");

	return _id;
}