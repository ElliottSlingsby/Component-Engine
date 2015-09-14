#include "AssetLoader.hpp"

#include <SDL_image.h>
#include <tiny_obj_loader.h>
#include <vector>

AssetLoader::~AssetLoader(){
	for (AssetMap::iterator i = _assets.begin(); i != _assets.end(); i++){
		delete i->second;
		i->second = 0;
	}
}

AssetLoader& AssetLoader::_instance(){
	static AssetLoader instance;
	return instance;
}

MeshData* AssetLoader::_loadMesh(std::string filepath){
	// tinyobj containers
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	// Error checking
	std::string error = tinyobj::LoadObj(shapes, materials, (_assetPath + filepath).c_str());

	if (!error.empty()){
		message_out("%s: %s %s!\n", "Asset Loader", "Cannot load mesh from file", (_assetPath + filepath).c_str());
		return 0;
	}

	// Vertex buffer
	int positionsSize = shapes[0].mesh.positions.size() * sizeof(float);
	int normalsSize = shapes[0].mesh.normals.size() * sizeof(float);
	int texcoordsSize = shapes[0].mesh.texcoords.size() * sizeof(float);
	int indicesSize = shapes[0].mesh.indices.size() * sizeof(unsigned int);

	// Setting up vertex buffer
	GLuint vertexBuffer = 0;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, positionsSize + normalsSize + texcoordsSize, 0, GL_STATIC_DRAW);

	// Filling vertex buffer
	glBufferSubData(GL_ARRAY_BUFFER, 0, positionsSize, &(shapes[0].mesh.positions)[0]);

	if (normalsSize)
		glBufferSubData(GL_ARRAY_BUFFER, positionsSize, normalsSize, &(shapes[0].mesh.normals)[0]);

	if (texcoordsSize)
		glBufferSubData(GL_ARRAY_BUFFER, positionsSize + normalsSize, texcoordsSize, &(shapes[0].mesh.texcoords)[0]);
	
	// Setting up index buffer
	GLuint indexBuffer = 0;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, &(shapes[0].mesh.indices[0]), GL_STATIC_DRAW);
	
	// Error checking and storing data
	GLenum err = glGetError();

	if (err != GL_NO_ERROR){
		message_out("%s: %s\n", "OpenGL Error", gluErrorString(err));
	}

	MeshData* asset = new MeshData(vertexBuffer, indexBuffer, indicesSize, positionsSize, texcoordsSize, normalsSize);
	_assets[filepath] = asset;

	return asset;
}

MaterialData* AssetLoader::_loadMaterial(std::string filepath){
	SDL_Surface* image = IMG_Load((_assetPath + filepath).c_str());

	if (!image){
		message_out("%s %s!", "Cannot load texture", (_assetPath + filepath).c_str());
		return 0;
	}
	
	// Gl ID creation
	GLuint id = 0;
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
	MaterialData* asset = new MaterialData(0, id, 0);
	_assets[filepath] = asset;

	return asset;
}

void AssetLoader::setAssetLocation(std::string filepath){
	_instance()._assetPath = "../" + filepath + "/";
}