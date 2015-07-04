#pragma once

#include <string>
#include <unordered_map>
#include <GL\glew.h>
#include <regex>

#define NULL_ASSET -1;


class AssetLoader{
	typedef std::unordered_map<std::string, GLuint> AssetMap;
	AssetMap _assets; // Map of binded GL IDs

	const char* _assetPath = "../asset/"; // Defualt asset location

	// Private singleton for use in static functions
	static AssetLoader& _instance();

	GLuint _loadTexture(std::string filepath);
	GLuint _loadMesh(std::string filepath); // Still work in progress

public:

	// Gets an asset if it's already loaded, but will also load and get the asset if not
	static GLuint getAsset(std::string filepath);
};