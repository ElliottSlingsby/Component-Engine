#include "NameBank.hpp"
#include <Static\DebugOutput.hpp>

using namespace Module;

std::string NameBank::getName(int id){
	IdNameMap::iterator nameIter = _idsToName.find(id);

	if (nameIter == _idsToName.end())
		return "";

	return nameIter->second;
}

void NameBank::getIds(const std::string& name, IntVector& intVector){
	NameIdMap::iterator idContainer = _nameToIds.find(name);

	if (idContainer == _nameToIds.end())
		return;

	intVector = idContainer->second;
}

void NameBank::bindName(int id, const std::string& name){
	IdNameMap::iterator nameIter = _idsToName.find(id);
	
	if (nameIter != _idsToName.end())
		_nameToIds.erase(nameIter->second);

	NameIdMap::iterator idContainer = _nameToIds.find(name);

	if (idContainer == _nameToIds.end()){
		_nameToIds[name] = IntVector();
	}
	else{
		if (std::find(_nameToIds[name].begin(), _nameToIds[name].end(), id) != _nameToIds[name].end()){
			message_out("%s: %s!\n", "Name Bank", "Name already bound to id");
			return;
		}
	}

	_nameToIds[name].push_back(id);
	_idsToName[id] = name;
}

void NameBank::unbindName(int id, const std::string& name){
	NameIdMap::iterator idContainer = _nameToIds.find(name);

	if (idContainer == _nameToIds.end()){
		message_out("%s: %s!\n", "Name Bank", "Name not bound to id");
		return;
	}

	IntVector::iterator idIter = std::find(_nameToIds[name].begin(), _nameToIds[name].end(), id);

	if (idIter == _nameToIds[name].end()){
		message_out("%s: %s!\n", "Name Bank", "Name not bound to id");
		return;
	}

	IdNameMap::iterator nameIter = _idsToName.find(id);

	if (nameIter == _idsToName.end()){
		message_out("%s: %s!\n", "Name Bank", "id not bound to name");
		return;
	}
	
	_idsToName.erase(nameIter);
	idContainer->second.erase(idIter);
	
	if (_nameToIds[name].size() == 0)
		_nameToIds.erase(name);
}