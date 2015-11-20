#include "Model.hpp"

#include <GL\glew.h>

Model::Model(const std::string& meshSrc, const std::string& materialSrc){
	_meshSrc = meshSrc;
	_materialSrc = materialSrc;
}

void Model::load(){
	_transform = getComponent<Transform>();

	if (_meshSrc != "")
		_mesh = AssetLoader::getAsset<MeshData>(_meshSrc);

	if (_materialSrc != "")
		_material = AssetLoader::getAsset<MaterialData>(_materialSrc);
}

void Model::setMesh(const MeshData* mesh){
	_mesh = mesh;
}

void Model::setMaterial(const MaterialData* material){
	_material = material;
}

void Model::render(){
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();

	// Translate based on Transform
	glTranslatef(-_transform->position().x, -_transform->position().y, -_transform->position().z);

	// Rotate based on Transform
	if (!_fixedRotation)
		glMultMatrixf(&glm::mat4_cast(_transform->rotation())[0][0]);

	// Scale based on Transform
	glScalef(-_transform->scale().x, -_transform->scale().y, _transform->scale().z);

	if (_material)
		glBindTexture(GL_TEXTURE_2D, _material->diffuse);
	else
		glBindTexture(GL_TEXTURE_2D, 0);

	bool switched = false;

	if (glIsEnabled(GL_LIGHTING) && _unlit){
		switched = true;
		glDisable(GL_LIGHTING);
	}

	draw();

	if (switched && _unlit)
		glEnable(GL_LIGHTING);

	glPopMatrix();
}

void Model::draw(){
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

void Model::setUnlit(bool unlit){
	_unlit = unlit;
}

void Model::setFixedRotation(bool fixedRotation){
	_fixedRotation = fixedRotation;
}