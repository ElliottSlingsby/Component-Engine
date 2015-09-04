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
		_transform = getComponent<Transform>();

		if (_meshSrc != "")
			_mesh = AssetLoader::getAsset<MeshData>(_meshSrc);

		if (_materialSrc != "")
			_material = AssetLoader::getAsset<MaterialData>(_materialSrc);
	}

	void setMesh(const MeshData* mesh){
		_mesh = mesh;
	}

	void setMaterial(const MaterialData* material){
		_material = material;
	}

	void render(){
		glMatrixMode(GL_MODELVIEW);

		glPushMatrix();

		// Translate based on Transform
		glTranslatef(-_transform->position().x, -_transform->position().y, -_transform->position().z);

		// Rotate based on Transform
		glm::vec3 eulerAngles = glm::eulerAngles(_transform->rotation());

		glRotatef(glm::degrees(eulerAngles.x), 1.f, 0.f, 0.f);
		glRotatef(glm::degrees(eulerAngles.y), 0.f, 1.f, 0.f);
		glRotatef(glm::degrees(eulerAngles.z), 0.f, 0.f, 1.f);
		
		// Scale based on Transform
		glScalef(_transform->scale().x, _transform->scale().y, _transform->scale().z);
		
		
		if (_material)
			glBindTexture(GL_TEXTURE_2D, _material->diffuse);
		else
			glBindTexture(GL_TEXTURE_2D, 0);
		
		draw();

		glPopMatrix();
	}

	virtual void draw(){
		if (_mesh){
			glBindBuffer(GL_ARRAY_BUFFER, _mesh->vertexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _mesh->indexBuffer);

			// Loading vertex data
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_FLOAT, 3 * sizeof(float), 0);

			// Loading normal data
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_FLOAT, 3 * sizeof(float), (void*)(_mesh->vertexSize));

			// Loading texture data
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_FLOAT, 2 * sizeof(float), (void*)(_mesh->vertexSize + _mesh->normalSize));

			glDrawElements(GL_TRIANGLES, _mesh->indicesSize, GL_UNSIGNED_INT, 0);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		}
	}
};