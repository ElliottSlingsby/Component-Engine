#include "AssetLoader.hpp"

#include "Module\SDLFunctions.hpp"
#include <Static\Renderer.hpp>

#include <SDL_image.h>
#include <tiny_obj_loader.h>
#include <vector>
#include <algorithm>

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
	glBufferSubData(GL_ARRAY_BUFFER, 0, positionsSize, &(mesh.positions)[0]);

	if (normalsSize)
		glBufferSubData(GL_ARRAY_BUFFER, positionsSize, normalsSize, &(mesh.normals)[0]);

	if (texcoordsSize)
		glBufferSubData(GL_ARRAY_BUFFER, positionsSize + normalsSize, texcoordsSize, &(mesh.texcoords)[0]);
	
	// Setting up index buffer
	GLuint indexBuffer = 0;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, &(mesh.indices[0]), GL_STATIC_DRAW);
	
	// Error checking and storing data
	GLenum err = glGetError();

	if (err != GL_NO_ERROR){
		message_out("%s: %s\n", "OpenGL Error", gluErrorString(err));
	}

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
		_renderer = SDL_CreateRenderer(Renderer::Window().window(), -1, SDL_RENDERER_ACCELERATED);

	SDL_Surface* image = IMG_Load((_assetPath + filepath).c_str());

	if (!image){
		message_out("%s %s!", "Cannot load texture", (_assetPath + filepath).c_str());
		return 0;
	}
	
	// Gl id creation
	GLuint id = 0;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	// Format check
	int format = GL_RGB;

	if (image->format->BytesPerPixel == 4)
		format = GL_RGBA;


	SDL_LockSurface(image);

	SDL_Surface* flipped = flipVertical(image);
	
	//SDL_FreeSurface(image);

	// Upload pixels
	glTexImage2D(GL_TEXTURE_2D, 0, format, flipped->w, flipped->h, 0, format, GL_UNSIGNED_BYTE, flipped->pixels);

	// Default parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Texture size
	glm::vec2 size(flipped->w, flipped->h);

	// Free the original surface
	SDL_FreeSurface(flipped);

	// Add to map
	MaterialData* asset = new MaterialData(0, id, 0, size);
	_assets[filepath] = asset;

	return asset;
}

void AssetLoader::setAssetLocation(const std::string& filepath){
	_instance()._assetPath = "../" + filepath + "/";
}