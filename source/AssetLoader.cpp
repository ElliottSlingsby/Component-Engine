#include "AssetLoader.hpp"

#include <algorithm>
#include <SDL_image.h>
#include <GL\glew.h>

AssetLoader& AssetLoader::_instance(){
	static AssetLoader instance;
	return instance;
}

GLuint AssetLoader::getAsset(std::string filepath){
	// OS specific, as Linux is case sensitive
	std::transform(filepath.begin(), filepath.end(), filepath.begin(), ::tolower);

	AssetMap::iterator iter = _instance()._assets.find(filepath.c_str());

	if (iter == _instance()._assets.end()){
		GLuint asset;

		if (std::regex_match(filepath, std::regex(".+\\.obj")))
			asset = _instance()._loadMesh(filepath);

		if (std::regex_match(filepath, std::regex(".+\\.(?:bmp|gif|jpeg|jpg|png|tga|tiff)")))
			asset = _instance()._loadTexture(filepath);

		return asset;
	}

	return iter->second;
}

GLuint AssetLoader::_loadTexture(std::string& filepath){
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

	_assets[filepath.c_str()] = id;

	return id;
}

GLuint AssetLoader::_loadMesh (std::string& filepath){
	printf("%s\n", filepath.c_str());

	return NULL_RESOURCE;
}