#include "AssetLoader.hpp"

#include <algorithm>
#include <SDL_image.h>
#include <GL\glew.h>
#include "Math\Vector2.hpp"
#include "Math\Vector3.hpp"
#include "Math\Vector4.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <list>

AssetLoader& AssetLoader::_instance(){
	static AssetLoader instance;
	return instance;
}

GLuint AssetLoader::getAsset(std::string filepath){
	// OS specific, as Linux is case sensitive. Should be ifdef'ed out
	std::transform(filepath.begin(), filepath.end(), filepath.begin(), ::tolower);

	AssetMap::iterator iter = _instance()._assets.find(filepath.c_str());

	// If asset isn't loaded, the nload
	if (iter == _instance()._assets.end()){
		GLuint asset = NULL_ASSET;

		// Regex search to determine file type
		if (std::regex_match(filepath, std::regex("^.+\\.obj$"))) // Meshes
			asset = _instance()._loadMesh(filepath);

		else if (std::regex_match(filepath, std::regex("^.+\\.(?:bmp|gif|jpeg|jpg|png|tga|tiff)$"))) // Textures
			asset = _instance()._loadTexture(filepath);

		else
			printf("%s: %s %s!\n", "Asset Loader", "Cannot load asset from file", filepath);

		return asset;
	}

	// If asset is loaded, then return already loaded version
	return iter->second;
}

GLuint AssetLoader::_loadTexture(std::string filepath){
	SDL_Surface* image = IMG_Load((_assetPath + filepath).c_str());

	if (!image){
		printf("%s %s!", "Cannot load texture", filepath.c_str());
		return NULL_ASSET;
	}

	// Gl ID creation
	GLuint id = -1;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	// Format check
	int format = GL_RGB;

	if (image->format->BytesPerPixel == 4)
		format = GL_RGBA;

	// Upload pixels
	glTexImage2D(GL_TEXTURE_2D, 0, format, image->w, image->h, 0, format, GL_UNSIGNED_BYTE, image->pixels);

	// Default parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Free the original surface
	SDL_FreeSurface(image);

	// Add to map
	_assets[filepath] = id;

	return id;
}

void explode(std::vector<std::string>& container, std::string line, char divider = ' '){
	bool reading = true;

	if (*line.begin() == divider)
		bool reading = false;

	int i = 0;

	int in = 0;
	int out = line.length() - 1;

	for (std::string::iterator iter = line.begin(); iter != line.end(); iter++){
		bool capture = false;

		if (reading && *iter == divider){
			out = i;
			reading = false;
			capture = true;
		}
		else if (!reading && *iter != divider){
			in = i;
			reading = true;
		}

		if (capture || i == line.length() - 1)
			container.push_back(line.substr(in, out - in));

		i++;
	}
}

GLuint AssetLoader::_loadMesh (std::string filepath){
	// Work in progress!
	// Will eventually read through obj files line by line

	std::ifstream file(_assetPath + filepath);

	if (!file.is_open()){
		printf("%s %s!", "Cannot load mesh", filepath.c_str());
		return NULL_ASSET;
	}

	typedef Vector3<GLfloat> Vector3Gl;
	typedef Vector2<GLfloat> Vector2Gl;

	std::list<Vector3Gl> vertices;
	std::list<Vector2Gl> textures;
	std::list<Vector3Gl> normals;

	while (file.good()){
		std::string line;
		getline(file, line);

		if (!line.size() || *line.begin() == '#')
			continue;

		std::vector<std::string> contents;
			
		explode(contents, line);

		if (contents[0] == "v"){
			vertices.push_back(Vector3Gl(
				std::stof(contents[1]),
				std::stof(contents[2]),
				std::stof(contents[3])
			));
		}
		else if (contents[0] == "vt"){
			textures.push_back(Vector2Gl(
				std::stof(contents[1]),
				std::stof(contents[2])
			));
		}
		else if (contents[0] == "vn"){
			normals.push_back(Vector3Gl(
				std::stof(contents[1]),
				std::stof(contents[2]),
				std::stof(contents[3])
			));
		}
	}

	//file.seekg(0, is.beg);
	
	GLuint id = NULL_ASSET;

	return id;
}