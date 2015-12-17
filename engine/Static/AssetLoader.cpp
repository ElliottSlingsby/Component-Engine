#include "AssetLoader.hpp"

#include <Static\SDLFunctions.hpp>
#include <Static\Renderer.hpp>

#include <SDL_image.h>
#include <tiny_obj_loader.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

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

MeshData* AssetLoader::_loadMesh(const std::string& filepath){

	_materialTextures(_assetPath + "material.mtl");


	// tinyobj containers
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	// Error checking
	std::string error = tinyobj::LoadObj(shapes, materials, (_assetPath + filepath).c_str());

	if (!error.empty()){
		message_out("%s: %s %s!\n", "Asset Loader", "Cannot load mesh from file", (_assetPath + filepath).c_str());
		return 0;
	}

	tinyobj::mesh_t mesh = shapes[0].mesh;

	// Vertex buffer
	int positionsSize = mesh.positions.size() * sizeof(float);
	int normalsSize = mesh.normals.size() * sizeof(float);
	int texcoordsSize = mesh.texcoords.size() * sizeof(float);
	int indicesSize = mesh.indices.size() * sizeof(unsigned int);

	// Setting up vertex buffer
	GLuint vertexBuffer = 0;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, positionsSize + normalsSize + texcoordsSize, 0, GL_STATIC_DRAW);

	// Filling vertex buffer
	glBufferSubData(GL_ARRAY_BUFFER, 0, positionsSize, &(mesh.positions)[0]); // Positions

	if (normalsSize)
		glBufferSubData(GL_ARRAY_BUFFER, positionsSize, normalsSize, &(mesh.normals)[0]); // Normals

	if (texcoordsSize)
		glBufferSubData(GL_ARRAY_BUFFER, positionsSize + normalsSize, texcoordsSize, &(mesh.texcoords)[0]); // Texcoords
	
	// Setting up index buffer
	GLuint indexBuffer = 0;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, &(mesh.indices[0]), GL_STATIC_DRAW);
	
	// Error checking and storing data
	//GLenum err = glGetError();
	//
	//if (err != GL_NO_ERROR){
	//	message_out("%s: %s\n", "OpenGL Error", gluErrorString(err));
	//}

	// Getting min and max of mesh
	glm::vec3 min(mesh.positions[0], mesh.positions[1], mesh.positions[2]);
	glm::vec3 max(min);

	for (unsigned int i = 0; i < mesh.positions.size() / 3; i++){
		if (mesh.positions[i] < min.x)
			min.x = mesh.positions[i];
		else if (mesh.positions[i] > max.x)
			max.x = mesh.positions[i];

		if (mesh.positions[i + 1] < min.x)
			min.x = mesh.positions[i + 1];
		else if (mesh.positions[i + 1] > max.x)
			max.x = mesh.positions[i + 1];

		if (mesh.positions[i + 2] < min.x)
			min.x = mesh.positions[i + 2];
		else if (mesh.positions[i + 2] > max.x)
			max.x = mesh.positions[i + 2];
	}

	// Bounding box lengths
	glm::vec3 size(min.x + max.x, min.y + max.y, min.z + max.z);

	MeshData* asset = new MeshData(vertexBuffer, indexBuffer, indicesSize, positionsSize, texcoordsSize, normalsSize, size);
	_assets[filepath] = asset;

	return asset;
}

MaterialData* AssetLoader::_loadMaterial(const std::string& filepath){
	if (!_renderer)
		_renderer = SDL_CreateRenderer(Renderer::window().sdlWindow(), -1, SDL_RENDERER_ACCELERATED);

	if (!_specularTexture){
		SDL_Surface* specular = IMG_Load((_assetPath + _defaultSpecular).c_str());

		if (!specular){
			error_out(("Cannot find default specular texture at " + _assetPath + _defaultSpecular).c_str());
		}

		_specularTexture = _createTexture(specular);
	}

	if (!_normalTexture){
		SDL_Surface* normal = IMG_Load((_assetPath + _defaultNormal).c_str());

		if (!normal){
			error_out(("Cannot find default normal texture at " + _assetPath + _defaultNormal).c_str());
		}

		_normalTexture = _createTexture(normal);
	}



	//SDL_Surface* image = IMG_Load((_assetPath + filepath).c_str());
	//
	//if (!image){
	//	message_out("%s %s!", "Cannot load texture", (_assetPath + filepath).c_str());
	//	return 0;
	//}

	GLuint diffuse = 0;
	GLuint specular = 0;
	GLuint normal = 0;

	glm::vec2 diffuseSize(0, 0);
	glm::vec2 specularSize(0, 0);
	glm::vec2 normalSize(0, 0);

	std::size_t dot = filepath.find(".");

	std::string extension = filepath.substr(dot);

	if (extension != ".mtl"){
		glm::vec3 diffuseTexture = _loadTexture(filepath);

		if (diffuseTexture.x != 0){
			diffuseSize = glm::vec2(diffuseTexture.y, diffuseTexture.z);
			diffuse = (int)diffuseTexture.x;
		}

		specular = _specularTexture;
		specularSize = glm::vec2(1, 1);

		normal = _normalTexture;
		normalSize = glm::vec2(1, 1);
	}
	else{
		StringVector textures;

		textures = _materialTextures(filepath);

		if (textures.size() < 1){
			message_out("Material file %s doesn't have enough channels!\n", filepath.c_str());
			return 0;
		}

		// Diffuse
		glm::vec3 diffuseTexture = _loadTexture(textures[0]);

		diffuse = (int)diffuseTexture.x;
		diffuseSize = glm::vec2(diffuseTexture.y, diffuseTexture.z);
		
		// Specular
		if (textures.size() > 1){
			glm::vec3 texture = _loadTexture(textures[1]);

			specular = (int)texture.x;
			specularSize = glm::vec2(texture.y, texture.z);
		}
		else{
			specular = _specularTexture;
			specularSize = glm::vec2(1, 1);
		}
		
		// Normal
		if (textures.size() > 2){
			glm::vec3 texture = _loadTexture(textures[2]);

			normal = (int)texture.x;
			normalSize = glm::vec2(texture.y, texture.z);
		}
		else{
			normal = _normalTexture;
			normalSize = glm::vec2(1, 1);
		}
	}
	
	// Add to map
	MaterialData* asset = new MaterialData(diffuse, specular, normal, diffuseSize, specularSize, normalSize);
	_assets[filepath] = asset;

	return asset;


	//SDL_Surface* image = IMG_Load((_assetPath + filepath).c_str());

	//diffuse = _createTexture(_assetPath + filepath + textures)

	// Texture size
	//glm::vec2 size(image->w, image->h);
	
	//diffuse = _createTexture(image);
	//specular = _createTexture(IMG_Load((_assetPath + "wood/diffuse.png").c_str())); // TESTING
	//normal = 0;


}

glm::vec3 AssetLoader::_loadTexture(const std::string& filepath){
	glm::vec2 size(0, 0);
	GLuint id = 0;

	if (_textures.find(filepath) == _textures.end()){
		std::string fullPath = _assetPath + filepath;

		SDL_Surface* surface = IMG_Load(fullPath.c_str());
		
		// Diffuse
		if (surface){
			size = glm::vec2(surface->w, surface->h);
			id = _createTexture(surface);

			_textures[filepath] = glm::vec3(id, size.x, size.y);
		}
	}

	return _textures[filepath];
}

void AssetLoader::setAssetLocation(const std::string& filepath){
	_instance()._assetPath = "../" + filepath + "/";
}

GLuint AssetLoader::_createTexture(SDL_Surface* surface){
	if (!surface)
		return 0;

	// Gl id creation
	GLuint id = 0;

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	// Format check
	int format = GL_RGB;

	if (surface->format->BytesPerPixel == 4)
		format = GL_RGBA;

	SDL_LockSurface(surface);

	SDL_Surface* flipped = flipVertical(surface);

	// Upload pixels
	glTexImage2D(GL_TEXTURE_2D, 0, format, flipped->w, flipped->h, 0, format, GL_UNSIGNED_BYTE, flipped->pixels);

	// Default parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Free the original surface
	SDL_FreeSurface(flipped);

	return id;
}

AssetLoader::StringVector AssetLoader::_materialTextures(const std::string& filepath){
	std::ifstream file(_assetPath + filepath);

	StringVector contents;

	if (file.is_open()){
		contents.reserve(3);

		int i = 0;
		for (std::string line; std::getline(file, line); i++){
			if (i == 3)
				break;

			contents.push_back(line);
		}
	}

	return contents;
}