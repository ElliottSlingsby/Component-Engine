#pragma once

#include <vector>
#include <string>
#include <unordered_map>

namespace Module{
	class NameBank{
		typedef std::vector<int> IntVector;
		typedef std::unordered_map<std::string, IntVector> NameIdMap;
		NameIdMap _nameToIds;

		typedef std::unordered_map<int, std::string> IdNameMap;
		IdNameMap _idsToName;

	public:
		std::string getName(int id);
		void getIds(const std::string& name, IntVector& intVector);

		void bindName(int id, const std::string& name);
		void unbindName(int id, const std::string& name = "");
	};
}