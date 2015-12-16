#pragma once

#include <GL\glew.h>
#include <unordered_map>
#include <algorithm>
#include <Static\DebugOutput.hpp>
#include <string>
#include <glm\vec3.hpp>
#include <glm\vec2.hpp>
#include <SDL.h>

struct Asset{
	virtual ~Asset(){}
};

struct MeshData : public Asset{
	const GLuint vertexBuffer;
	const GLuint indexBuffer;

	const unsigned int indicesSize;
	const unsigned int vertexSize;
	const unsigned int textureSize;
	const unsigned int normalSize;

	const glm::vec3 size;

	MeshData(GLuint vertexBuffer, GLuint indexBuffer, unsigned int indicesSize, unsigned int vertexSize, unsigned int textureSize, unsigned int normalSize, glm::vec3 size) :
		vertexBuffer(vertexBuffer), 
		indexBuffer(indexBuffer), 
		indicesSize(indicesSize),
		vertexSize(vertexSize),
		textureSize(textureSize),
		normalSize(normalSize),
		size(size){
	}

	~MeshData(){
		glDeleteBuffers(1, &vertexBuffer);
		glDeleteBuffers(1, &indexBuffer);
	}
};

struct MaterialData : public Asset{
	const GLuint specular;
	const GLuint diffuse;
	const GLuint ambient;

	const glm::vec2 specularSize;
	const glm::vec2 diffuseSize;
	const glm::vec2 ambientSize;

	MaterialData(GLuint diffuse, GLuint specular, GLuint ambient, glm::vec2 diffuseSize, glm::vec2 specularSize, glm::vec2 ambientSize) :
		specular(specular), 
		diffuse(diffuse), 
		ambient(ambient),
		diffuseSize(diffuseSize),
		specularSize(specularSize),
		ambientSize(ambientSize){
	}

	~MaterialData(){
		glDeleteTextures(1, &specular);
		glDeleteTextures(1, &diffuse);
		glDeleteTextures(1, &ambient);
	}
};

class AssetLoader{
	typedef std::unordered_map<std::string, Asset*> AssetMap;
	AssetMap _assets;

	std::string _assetPath = "../"; // Default asset location

	SDL_Renderer* _renderer = 0;

	typedef std::vector<std::string> StringVector;
	typedef std::unordered_map<std::string, glm::vec3> Vec3Map;

	Vec3Map _textures;

	std::string _defaultNormal = "default/normal.png";
	std::string _defaultSpecular = "default/specular.png";

	GLuint _ambientTexture = 0;
	GLuint _specularTexture = 0;

	// Private singleton for use in static functions
	static AssetLoader& _instance();

	MeshData* _loadMesh(const std::string& filepath);
	MaterialData* _loadMaterial(const std::string& filepath);
	glm::vec3 _loadTexture(const std::string& filepath);

	GLuint _createTexture(SDL_Surface* surface);

	StringVector _materialTextures(const std::string& filepath);


	~AssetLoader();

public:
	// Gets an asset if it's already loaded, but will also load and get the asset if not

	template <typename T>
	static const T* getAsset(std::string filepath){
		// Case sensitivity may cause issues on non windows machines
		std::transform(filepath.begin(), filepath.end(), filepath.begin(), ::tolower);

		AssetMap::iterator iter = _instance()._assets.find(filepath.c_str());

		// If asset isn't loaded, then load
		if (iter == _instance()._assets.end()){
			Asset* asset = 0;

			if (typeid(T) == typeid(MeshData))
				asset = _instance()._loadMesh(filepath);

			else if (typeid(T) == typeid(MaterialData))
				asset = _instance()._loadMaterial(filepath);

			else
				message_out("%s: %s %s!\n", "Asset Loader", "Unknown asset type", filepath);

			return dynamic_cast<const T*>(asset);
		}

		// If asset is loaded, then return already loaded version
		return dynamic_cast<const T*>(iter->second);
	}

	static void setAssetLocation(const std::string& filepath);
};