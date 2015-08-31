#pragma once

#include <string>
#include <unordered_map>
#include <GL\glew.h>
#include <vector>
#include <GL\glew.h>
#include <algorithm>
#include "Static\DebugPrint.hpp"

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

	MeshData(GLuint vertexBuffer, GLuint indexBuffer, unsigned int indicesSize, unsigned int vertexSize, unsigned int textureSize, unsigned int normalSize) :
		vertexBuffer(vertexBuffer), 
		indexBuffer(indexBuffer), 
		indicesSize(indicesSize),
		vertexSize(vertexSize),
		textureSize(textureSize),
		normalSize(normalSize){
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

	MaterialData(GLuint specular , GLuint diffuse, GLuint ambient) : 
		specular(specular), 
		diffuse(diffuse), 
		ambient(ambient){
	}

	~MaterialData(){
		glDeleteTextures(1, &specular);
		glDeleteTextures(1, &diffuse);
		glDeleteTextures(1, &ambient);
	}
};

class AssetLoader{
	typedef std::unordered_map<std::string, const Asset*> AssetMap;
	AssetMap _assets;

	const char* _assetPath = "../asset/"; // Defualt asset location

	// Private singleton for use in static functions
	static AssetLoader& _instance();

	MeshData* _loadMesh(std::string filepath);
	MaterialData* _loadMaterial(std::string filepath);

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

			// Regex search to determine file type
			if (typeid(T) == typeid(MeshData))
				asset = _instance()._loadMesh(filepath);

			else if (typeid(T) == typeid(MaterialData))
				asset = _instance()._loadMaterial(filepath);

			else
				printd("%s: %s %s!\n", "Asset Loader", "Unknown asset type", filepath);

			return dynamic_cast<const T*>(asset);
		}

		// If asset is loaded, then return already loaded version
		return dynamic_cast<const T*>(iter->second);
	}
};