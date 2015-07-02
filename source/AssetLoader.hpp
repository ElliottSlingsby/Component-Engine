#pragma once

#include <string>
#include <unordered_map>
#include <GL\glew.h>
#include <regex>

#define NULL_RESOURCE -1;
/*

OBJ Regex patterns:

Vertices
v +(-*\d+.\d+) +(-*\d+.\d+) +(-*\d+.\d+)
v +(?:(-*\d+.\d+) *){3}

Normals
vn +(-*\d+.\d+) +(-*\d+.\d+) +(-*\d+.\d+)
vn +(?:(-*\d+.\d+) *){3}

UVs
vt +(-*\d+.\d+) +(-*\d+.\d+) +(-*\d+.\d+)
vt +(?:(-*\d+.\d+) *){3}

Faces
f +(\d+)\/(\d+)\/(\d+) +(\d+)\/(\d+)\/(\d+) +(\d+)\/(\d+)\/(\d+)
f +(?:(\d+)\/(\d+)\/(\d+) *){3}
f +(?:(?:(\d+)\/*){3} *){3}

g +([\s\S]+)
s +(\d+)

*/

class AssetLoader{
	typedef std::unordered_map<const char*, GLuint> AssetMap;
	AssetMap _assets;

	const char* _assetPath = "../asset/";

	static AssetLoader& _instance();

	GLuint _loadTexture(std::string& filepath);
	GLuint _loadMesh(std::string& filepath);

public:

	static GLuint getAsset(std::string filepath);
};