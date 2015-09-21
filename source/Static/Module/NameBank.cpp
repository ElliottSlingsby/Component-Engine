#include "NameBank.hpp"
#include <Static\DebugOutput.hpp>

int Module::NameBank::generateId(){
	if (_removed.empty()){
		// Create new one
		_highest++;
		return _highest - 1;
	}

	// Otherwise pop off used one
	int id = _removed.top();
	_removed.pop();

	return id;
}

void Module::NameBank::deleteId(int id){
	if (id == -1){
		message_out("%s: %s!\n", "Name Bank", "Can't delete null ID");
		return;
	}
	
	// If id was at the top
	if (id == _highest - 1){
		_highest--;
		return;
	}

	// Otherwise add it to the removed pile
	_removed.push(id);
}

std::string Module::NameBank::getName(int id){
	IdNameMap::iterator nameIter = _idsToName.find(id);

	if (nameIter == _idsToName.end()){
		message_out("%s: %s!\n", "Name Bank", "ID isn't bound to a name");
		return "";
	}

	return nameIter->second;
}

void Module::NameBank::getIds(const std::string& name, IntVector& intVector){
	NameIdMap::iterator idContainer = _nameToIds.find(name);

	if (idContainer == _nameToIds.end()){
		message_out("%s: %s!\n", "Name Bank", "Name isn't bound to an ID");
		return;
	}

	intVector = idContainer->second;
}

void Module::NameBank::bindName(int id, const std::string& name){
	IdNameMap::iterator nameIter = _idsToName.find(id);
	
	if (nameIter != _idsToName.end())
		_nameToIds.erase(nameIter->second);

	NameIdMap::iterator idContainer = _nameToIds.find(name);

	if (idContainer == _nameToIds.end()){
		_nameToIds[name] = IntVector();
	}
	else{
		if (std::find(_nameToIds[name].begin(), _nameToIds[name].end(), id) != _nameToIds[name].end()){
			message_out("%s: %s!\n", "Name Bank", "Name already bound to ID");
			return;
		}
	}

	_nameToIds[name].push_back(id);
	_idsToName[id] = name;
}

void Module::NameBank::unbindName(int id, const std::string& name){
	NameIdMap::iterator idContainer = _nameToIds.find(name);

	if (idContainer == _nameToIds.end()){
		message_out("%s: %s!\n", "Name Bank", "Name not bound to ID");
		return;
	}

	IntVector::iterator idIter = std::find(_nameToIds[name].begin(), _nameToIds[name].end(), id);

	if (idIter == _nameToIds[name].end()){
		message_out("%s: %s!\n", "Name Bank", "Name not bound to ID");
		return;
	}

	IdNameMap::iterator nameIter = _idsToName.find(id);

	if (nameIter == _idsToName.end()){
		message_out("%s: %s!\n", "Name Bank", "ID not bound to name");
		return;
	}
	
	_idsToName.erase(nameIter);
	idContainer->second.erase(idIter);



	if (_nameToIds[name].size() == 0)
		_nameToIds.erase(name);
}