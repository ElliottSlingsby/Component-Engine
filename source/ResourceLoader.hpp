#pragma once

#include <string>
#include <unordered_map>

class Resource{

};

class ResourceLoader{
	std::unordered_map<std::string, Resource*> _resources;

	ResourceLoader(){}

	static ResourceLoader& _instance(){
		static ResourceLoader instance;
		return instance;
	}

	std::string& _formatPath(std::string& filepath){}

	bool _loadTexture(std::string filepath){}
	bool _loadMesh(std::string filepath){}

public:
	template <typename T>
	static void load(std::string filepath, void (*callback)(T* resource)){}

	template <typename T>
	static T* get(std::string filepath){}
};