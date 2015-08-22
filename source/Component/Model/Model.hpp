#pragma once

#include "Entity\HelperComponent.hpp"
#include <GL\glew.h>
#include "Static\AssetLoader.hpp"

class Model : public HelperComponent{
protected:
	Transform* _transform = 0;

	std::string _meshSrc = "";
	std::string _materialSrc = "";

	const MeshData* _mesh = 0;
	const MaterialData* _material = 0;

public:
	Model(std::string meshSrc, std::string materialSrc = ""){
		_meshSrc = meshSrc;
		_materialSrc = materialSrc;
	}

	void load(){
		_transform = _getComponent<Transform>();

		if (_meshSrc != "")
			_mesh = AssetLoader::getAsset<MeshData>(_meshSrc);

		if (_materialSrc != "")
			_material = AssetLoader::getAsset<MaterialData>(_materialSrc);
	}

	void render(){
		glMatrixMode(GL_MODELVIEW);

		glPushMatrix();

		// Translate based on Transform
		glTranslatef(_transform->position().x(), _transform->position().y(), _transform->position().z());

		// Rotate based on Transform
		glRotatef(_transform->rotation().x(), 1.f, 0.f, 0.f);
		glRotatef(_transform->rotation().y(), 0.f, 1.f, 0.f);
		glRotatef(_transform->rotation().z(), 0.f, 0.f, 1.f);

		// Scale based on Transform
		glScalef(_transform->scale().x(), _transform->scale().y(), _transform->scale().z());
		
		if (_material)
			glBindTexture(GL_TEXTURE_2D, _material->diffuse);
		else
			glBindTexture(GL_TEXTURE_2D, 0);

		draw();

		glPopMatrix();
	}

	virtual void draw(){
		glBindBuffer(GL_ARRAY_BUFFER, _mesh->vertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _mesh->indexBuffer);

		glDrawElements(GL_TRIANGLES, _mesh->size, GL_UNSIGNED_INT, 0);
	}
};