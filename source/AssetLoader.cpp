#include "AssetLoader.hpp"

#include <algorithm>
#include <SDL_image.h>
#include <GL\glew.h>
#include <glm\vec2.hpp>
#include <glm\vec3.hpp>
#include <fstream>
#include <string>

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
		GLuint asset;

		if (std::regex_match(filepath, std::regex("^.+\\.obj$"))) // Regex file extension check
			asset = _instance()._loadMesh(filepath);

		if (std::regex_match(filepath, std::regex("^.+\\.(?:bmp|gif|jpeg|jpg|png|tga|tiff)$"))) //  Regex file extension check
			asset = _instance()._loadTexture(filepath);

		return asset;
	}

	// If asset is loaded, then return already loaded version
	return iter->second;
}

GLuint AssetLoader::_loadTexture(std::string filepath){
	SDL_Surface* image = IMG_Load((_assetPath + filepath).c_str());

	if (!image){
		printf("%s %s!", "Cannot load texture", filepath.c_str());
		return NULL_RESOURCE;
	}

	// Gl ID creation
	GLuint id = -1;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	// Format check
	int format = GL_RGB;

	if (image->format->BytesPerPixel == 4)
		format = GL_RGBA;

	// Send pixels
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

GLuint AssetLoader::_loadMesh (std::string filepath){
	// Work in progress!
	// Will eventually read through obj files line by line

	/*std::ifstream file(_assetPath + filepath);

	if (!file.is_open()){
		printf("%s %s!", "Cannot load mesh", filepath.c_str());
		return NULL_RESOURCE;
	}

	// Counters
	unsigned int v_i = 0;
	unsigned int vn_i = 0;
	unsigned int vt_i = 0;
	unsigned int f_i = 0;

	while (file.good()){
		std::string line;
		getline(file, line);

		std::string type = line.substr(0, line.find(' '));

		if (type == "v" || type == "vn" || type == "vt"){
			std::string first = line.substr(line.find(' ') + 1);

			std::string second = first.substr(line.find(' ') + 1);

			std::string third = second.substr(line.find(' ') + 1);

			//printf("%s | %s | %s\n", first.c_str(), second.c_str(), third.c_str());

			printf("|%s|\n", first.c_str());

			if (type == "v")
				v_i++;
			if (type == "vn")
				vn_i++;
			if (type == "vt")
				vt_i++;
		}
		else if (type == "f"){

			f_i++;
		}
	}

	//file.seekg(0, is.beg);*/
	
	GLuint id = NULL_RESOURCE;

	return id;
}