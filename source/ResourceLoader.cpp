#include "ResourceLoader.hpp"

#include <algorithm>
#include <SDL_image.h>
#include <GL\glew.h>

ResourceLoader& ResourceLoader::_instance(){
	static ResourceLoader instance;
	return instance;
}

GLuint ResourceLoader::getResource(std::string filepath){
	// OS specific, as Linux is case sensitive
	std::transform(filepath.begin(), filepath.end(), filepath.begin(), ::tolower);

	ResourceMap::iterator iter = _instance()._resources.find(filepath.c_str());

	if (iter == _instance()._resources.end()){
		GLuint resource;

		if (std::regex_match(filepath, std::regex(".+\\.obj")))
			resource = _instance()._loadMesh(filepath);

		if (std::regex_match(filepath, std::regex(".+\\.(?:bmp|gif|jpeg|jpg|png|tga|tiff)")))
			resource = _instance()._loadTexture(filepath);

		return resource;
	}

	return iter->second;
}

GLuint ResourceLoader::_loadTexture(std::string& filepath){
	SDL_Surface* image = IMG_Load((_assetPath + filepath).c_str());

	if (!image){
		printf("%s %s!", "Cannot load texture", filepath.c_str());
		return NULL_RESOURCE;
	}

	GLuint id = -1;

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	int format = GL_RGB;

	if (image->format->BytesPerPixel == 4)
		format = GL_RGBA;

	glTexImage2D(GL_TEXTURE_2D, 0, format, image->w, image->h, 0, format, GL_UNSIGNED_BYTE, image->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	SDL_FreeSurface(image);

	_resources[filepath.c_str()] = id;

	return id;
}

GLuint ResourceLoader::_loadMesh (std::string& filepath){
	printf("%s\n", filepath.c_str());

	return NULL_RESOURCE;
}