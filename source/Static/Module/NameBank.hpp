#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <stack>
#include <set>

class Identifier{
	std::string _name = "";
	int _id = -1;

public:
	std::string name();
	int id();

	void setName(const std::string& name);
	void setId(int id);
};

namespace Module{
	class NameBank{
		typedef std::vector<int> IntVector;
		typedef std::unordered_map<std::string, IntVector> NameIdMap;
		NameIdMap _nameToIds;

		typedef std::unordered_map<int, std::string> IdNameMap;
		IdNameMap _idsToName;
		
		std::stack<int> _removed;
		int _highest = 0;

	public:
		int generateId();
		void deleteId(int id);

		std::string getName(int id);
		void getIds(const std::string& name, IntVector& intVector);

		void bindName(int id, const std::string& name);
		void unbindName(int id, const std::string& name = "");
	};
}