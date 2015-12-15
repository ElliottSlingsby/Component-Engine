#include "Model.hpp"

#include <GL\glew.h>
#include <Static\Renderer.hpp>

//https://open.gl/textures
//https://www.opengl.org/wiki/Sampler_(GLSL)
//http://www.geeks3d.com/20110908/opengl-3-3-sampler-objects-control-your-texture-units/
//https://www.opengl.org/discussion_boards/showthread.php/163092-Passing-Multiple-Textures-from-OpenGL-to-GLSL-shader
//https://en.wikibooks.org/wiki/OpenGL_Programming/Advanced/GLSL


#define BUFFER_OFFSET(bytes) ((GLubyte*)NULL + (bytes))

Model::Model(const std::string& meshSrc, const std::string& materialSrc, const std::string& shader){
	_meshSrc = meshSrc;
	_materialSrc = materialSrc;

	if (shader != "")
		_shader = shader;
}

void Model::load(){
	_transform = getComponent<Transform>();

	if (_meshSrc != "")
		_mesh = AssetLoader::getAsset<MeshData>(_meshSrc);

	if (_materialSrc != "")
		_material = AssetLoader::getAsset<MaterialData>(_materialSrc);

	//if (_mesh){
	//	glEnableVertexAttribArray(0); // Positions
	//	glVertexAttribPointer(_mesh->vertexBuffer, _mesh->vertexSize, GL_FLOAT, GL_FALSE, sizeof(float)* 3, BUFFER_OFFSET(0));
	//	
	//	glEnableVertexAttribArray(1); // Normals
	//	glVertexAttribPointer(_mesh->vertexBuffer, _mesh->vertexSize, GL_FLOAT, GL_FALSE, sizeof(float)* 3, BUFFER_OFFSET(_mesh->vertexSize));
	//	
	//	glEnableVertexAttribArray(2); // Texcoords
	//	glVertexAttribPointer(_mesh->vertexBuffer, _mesh->vertexSize, GL_FLOAT, GL_FALSE, sizeof(float)* 2, BUFFER_OFFSET(_mesh->vertexSize + _mesh->normalSize));
	//}
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



	//GLuint program = Renderer::shaderManager().currentProgram();
	//Renderer::shaderManager().useProgram(_shader);


	if (_material){	
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _material->diffuse);

		//glActiveTexture(GL_TEXTURE0 + 1);
		//glBindTexture(GL_TEXTURE_2D, _material->specular);
		//
		//glActiveTexture(GL_TEXTURE0 + 2);
		//glBindTexture(GL_TEXTURE_2D, _material->diffuse);

		//GLint diffuse = glGetUniformLocation(Renderer::shaderManager().currentProgram(), "uniform_diffuse");
		//Renderer::shaderManager().uniform(diffuse, _material->diffuse);
	}
	else
		glBindTexture(GL_TEXTURE_2D, 0);

	

	bool switched = false;

	if (glIsEnabled(GL_LIGHTING) && _unlit){
		switched = true;
		glDisable(GL_LIGHTING);
	}
	

	//if (_material && _shader != "main"){
	//	GLint diffuse = glGetUniformLocation(Renderer::shaderManager().currentProgram(), "uniform_diffuse");
	//
	//	Renderer::shaderManager().uniform(diffuse, _material->diffuse);
	//
	//	//Renderer::shaderManager()._glSimpleErrorCheck();
	//}

	//if (_shader == "main")
	//	Renderer::shaderManager().uniform(0, glm::vec3(1, 1, 1));

	draw();

	//Renderer::shaderManager().useProgram(program);

	if (switched && _unlit)
		glEnable(GL_LIGHTING);

	glPopMatrix();
}

void Model::draw(){
	if (_mesh){
		glBindBuffer(GL_ARRAY_BUFFER, _mesh->vertexBuffer);

		
		// Loading vertex data
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 3 * sizeof(float), 0);

		// Loading normal data
		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_FLOAT, 3 * sizeof(float), (void*)(_mesh->vertexSize));
		
		// Loading texture data
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 2 * sizeof(float), (void*)(_mesh->vertexSize + _mesh->normalSize));



		GLuint program = Renderer::shaderManager().currentProgram();

		GLint position = glGetAttribLocation(program, "in_position");
		GLint normal = glGetAttribLocation(program, "in_normal"); 
		GLint texcoord = glGetAttribLocation(program, "in_texcoord");
			



		if (position != -1){
			glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(position); // Positions
		}

		if (normal != -1){
			glVertexAttribPointer(normal, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(_mesh->vertexSize));
			glEnableVertexAttribArray(normal); // Normals
		}

		if (texcoord != -1){
			glVertexAttribPointer(texcoord, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(_mesh->vertexSize + _mesh->normalSize));
			glEnableVertexAttribArray(texcoord); // Texcoords
		}


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _mesh->indexBuffer);

		glDrawElements(GL_TRIANGLES, _mesh->indicesSize, GL_UNSIGNED_INT, 0); 

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}
}

void Model::setUnlit(bool unlit){
	_unlit = unlit;
}

void Model::setFixedRotation(bool fixedRotation){
	_fixedRotation = fixedRotation;
}