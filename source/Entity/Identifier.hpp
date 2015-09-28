#pragma once
// Base class for both Component and Entity classes

#define NULL_ID -1

class Identifier{
	int _id = NULL_ID;

public:
	virtual ~Identifier(){}

	void setID(int id);
	int id();
};