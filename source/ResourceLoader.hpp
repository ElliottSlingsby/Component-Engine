#pragma once

#include <string>
#include <unordered_map>
#include <GL\glew.h>
#include <regex>

/*

Regex patterns:

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

class ResourceLoader{
	//std::unordered_map<const char*, GLuint> _;

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