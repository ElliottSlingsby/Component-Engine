#pragma once

#include <string>
#include <unordered_map>
#include <GL\glew.h>
#include <regex>

#define NULL_RESOURCE -1;


class AssetLoader{
	typedef std::unordered_map<std::string, GLuint> AssetMap;
	AssetMap _assets;

	const char* _assetPath = "../asset/";

	static AssetLoader& _instance();

	GLuint _loadTexture(std::string filepath);
	GLuint _loadMesh(std::string filepath);

public:

	static GLuint getAsset(std::string filepath);
};