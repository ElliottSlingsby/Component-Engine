#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <stack>

class Identifier{
	std::string _name = "";
	int _id = -1;

public:
	std::string name();
	int id();

	void setName(std::string name);
	void setId(int id);
};

namespace Module{
	class NameBank{
		typedef std::vector<int> IntVector;
		typedef std::unordered_map<std::string, IntVector> EntityNameMap;
		EntityNameMap _names;

		std::stack<int> _removed;
		int _highest = 0;

	public:
		int generateId();
		void deleteId(int id);

		std::string getName(int id);
		void getIds(std::string name, IntVector& intVector);

		void bindName(int id, std::string name);
		void unbindName(int id, std::string name = "");
	};
}