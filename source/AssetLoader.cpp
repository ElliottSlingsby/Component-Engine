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
#include <tuple>

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
	GLuint id = NULL_ASSET;
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
		reading = false;

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

typedef std::tuple<GLfloat, GLfloat, GLfloat> Vertex;
typedef std::tuple<GLfloat, GLfloat> Texture;
typedef std::tuple<GLfloat, GLfloat, GLfloat> Normal;
typedef std::tuple<int, int, int> Corner;
typedef std::tuple<Corner, Corner, Corner> Face;

GLuint AssetLoader::_loadMesh (std::string filepath){
	std::ifstream file(_assetPath + filepath);

	if (!file.is_open()){
		printf("%s %s!", "Cannot load mesh", filepath.c_str());
		return NULL_ASSET;
	}

	std::list<Vertex> verticesTemp;
	std::list<Texture> texturesTemp;
	std::list<Normal> normalsTemp;
	std::list<Face> facesTemp;

	while (file.good()){
		std::string line;
		getline(file, line);

		if (line.size() == 0 || *line.begin() == '#')
			continue;

		std::vector<std::string> contents;
			
		explode(contents, line);

		if (contents[0] == "v")
			verticesTemp.push_back(std::make_tuple(std::stof(contents[1]), std::stof(contents[2]), std::stof(contents[3])));

		else if (contents[0] == "vt")
			texturesTemp.push_back(std::make_tuple(std::stof(contents[1]), std::stof(contents[2])));

		else if (contents[0] == "vn")
			normalsTemp.push_back(std::make_tuple(std::stof(contents[1]), std::stof(contents[2]), std::stof(contents[3])));
		
		else if (contents[0] == "f"){
			Corner corners[3];

			for (unsigned int i = 1; i < contents.size(); i++){
				std::vector<std::string> point;
				explode(point, contents[i], '/');

				corners[i - 1] = std::make_tuple(std::stoi(point[0]), std::stoi(point[1]), std::stoi(point[2]));
			}

			facesTemp.push_back(std::make_tuple(corners[0], corners[1], corners[2]));
		}
	}

	/*std::vector<Vertex> vertices = { std::begin(verticesTemp), std::end(verticesTemp) };
	std::vector<Texture> textures = { std::begin(texturesTemp), std::end(texturesTemp) };
	std::vector<Normal> normals = { std::begin(normalsTemp), std::end(normalsTemp) };
	std::vector<Face> faces = { std::begin(facesTemp), std::end(facesTemp) };

	GLuint id = NULL_ASSET;
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);

	//&vertices[0]

	glBufferData(
		GL_ARRAY_BUFFER,
		vertices.size() * sizeof(Vertex),
		&vertices[0],
		GL_STATIC_DRAW
	);
	
	return id;*/

	return NULL_ASSET;
}