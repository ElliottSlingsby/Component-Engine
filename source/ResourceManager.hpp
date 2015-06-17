#pragma once

/*
Resource manager will act as flyweight for meshes and textures.

Meshes and textures will be stored using their file path as a key.
Filepath keys will need to be formatted and made relative as avoid duplications.

ResourceManager will be a private singleton, only publicly accessible through static functions.

Loading should be multi threaded if possible.
This may make runtime loading super difficult though.

Public static functions will be unthreaded when called, only to then initiate the threads using private methods.
*/

#include <string>
#include <unordered_map>

class Resource{

};

class ResourceManager{
	std::unordered_map<std::string, Resource*> _resources;

	ResourceManager(){}

	static ResourceManager& _instance(){
		static ResourceManager instance;
		return instance;
	}

	std::string& _formatPath(std::string& filepath){}

	bool _loadTexture(std::string filepath){}
	bool _loadMesh(std::string filepath){}
	//Above methods should be called in another thread during runtime

public:
	template <typename T>
	static void load(std::string filepath, void (*callback)(T* resource)){}

	template <typename T>
	static T* get(std::string filepath){}

	//loads assets depending on file extension
	//requires callback as it will be threaded and may take time
};