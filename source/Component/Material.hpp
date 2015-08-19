#pragma once

#include "Base\HelperComponent.hpp"
#include "AssetLoader.hpp"
#include <GL\glew.h>

class Material : public HelperComponent{
	//std::string _ambient_src;
	//std::string _specular_src;
	std::string _diffuse_src;
	
	const MaterialData* _data;
	
public:
	Material(std::string image){
		_diffuse_src = image;
	}

	~Material(){
		//glDeleteTextures(1, &_diffuse);
	}

	Component* clone(){
		return new Material(_diffuse_src);
	}

	void load(){
		_data = AssetLoader::getNewAsset<MaterialData>(_diffuse_src);
	}

	void use(){
		glBindTexture(GL_TEXTURE_2D, _data->diffuse);
	}
};