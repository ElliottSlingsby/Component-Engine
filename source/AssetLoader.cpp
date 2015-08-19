#include "AssetLoader.hpp"

#include <SDL_image.h>
#include <tiny_obj_loader.h>

AssetLoader::~AssetLoader(){
	// Delete everything!
}

AssetLoader& AssetLoader::_instance(){
	static AssetLoader instance;
	return instance;
}

GLuint AssetLoader::getAsset(std::string filepath){
	// OS specific, as Linux is case sensitive. Should be ifdef'ed out
	std::transform(filepath.begin(), filepath.end(), filepath.begin(), ::tolower);

	AssetMap::iterator iter = _instance()._assets.find(filepath.c_str());

	// If asset isn't loaded, then load
	if (iter == _instance()._assets.end()){
		GLuint asset = 0;

		// Regex search to determine file type
		if (std::regex_match(filepath, std::regex("^.+\\.obj$"))) // Meshes (contains materials)
			asset = _instance()._loadMesh(filepath);

		else if (std::regex_match(filepath, std::regex("^.+\\.mtl$"))) // Materials (contains textures)
			asset = _instance()._loadMaterial(filepath);

		else if (std::regex_match(filepath, std::regex("^.+\\.(?:bmp|gif|jpeg|jpg|png|tga|tiff)$"))) // Textures
			asset = _instance()._loadTexture(filepath);

		else
			printf("%s: %s %s!\n", "Asset Loader", "Unknown asset type", filepath);

		return asset;
	}

	// If asset is loaded, then return already loaded version
	return iter->second;
}

GLuint AssetLoader::_loadMesh(std::string filepath){
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string error = tinyobj::LoadObj(shapes, materials, (_assetPath + filepath).c_str());

	if (!error.empty()){
		printf("%s: %s %s!\n", "Asset Loader", "Cannot load mesh from file", (_assetPath + filepath).c_str());
		return 0;
	}

	GLuint id = 0;
	glGenBuffers(2, &id);

	//int normals_s = shapes[0].mesh.normals.size() * sizeof(float);
	//int textures_s = shapes[0].mesh.texcoords.size() * sizeof(float);
	int positions_s = shapes[0].mesh.positions.size() * sizeof(float);
	int indices_s = shapes[0].mesh.indices.size() * sizeof(unsigned int);
	
	//int total = normals_s + textures_s + positions_s + indices_s;

	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, positions_s, &(shapes[0].mesh.positions[0]), GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_s, &(shapes[0].mesh.indices[0]), GL_STATIC_DRAW);

	//glBufferSubData(GL_ARRAY_BUFFER, 0, indices_s, &(shapes[0].mesh.indices)[0]);
	//glBufferSubData(GL_ARRAY_BUFFER, indices_s, positions_s, &(shapes[0].mesh.positions)[0]);
	//glBufferSubData(GL_ARRAY_BUFFER, indices_s + positions_s, normals_s, &(shapes[0].mesh.normals)[0]);
	//glBufferSubData(GL_ARRAY_BUFFER, indices_s + positions_s + normals_s, textures_s, &(shapes[0].mesh.texcoords)[0]);
	
	//&(shapes[0].mesh.positions)[0];

	//glBufferData(GL_ARRAY_BUFFER, )

	//for (std::vector<tinyobj::shape_t>::iterator i = shapes.begin(); i != shapes.end(); i++){
	//}

	GLenum err = glGetError();

	if (err != GL_NO_ERROR){
		printf("DAKJSDLKJASL:DK");
	}

	return id;
}

GLuint AssetLoader::_loadMaterial(std::string filepath){
	return 0;
}

GLuint AssetLoader::_loadTexture(std::string filepath){
	SDL_Surface* image = IMG_Load((_assetPath + filepath).c_str());

	if (!image){
		printf("%s %s!", "Cannot load texture", (_assetPath + filepath).c_str());
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
	_assets[filepath] = id;

	return id;
}


MeshData* AssetLoader::_loadNewMesh(std::string filepath){
	MeshData* asset = new MeshData(0, 0, 0);
	return asset;
}

MaterialData* AssetLoader::_loadNewMaterial(std::string filepath){
	SDL_Surface* image = IMG_Load((_assetPath + filepath).c_str());

	if (!image){
		printf("%s %s!", "Cannot load texture", (_assetPath + filepath).c_str());
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
	_newAssets[filepath] = asset;
	return asset;
}