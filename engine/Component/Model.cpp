#include "Model.hpp"

#include <GL\glew.h>
#include <Static\Renderer.hpp>
#include <Static\Utils.hpp>

//https://open.gl/textures
//https://www.opengl.org/wiki/Sampler_(GLSL)
//http://www.geeks3d.com/20110908/opengl-3-3-sampler-objects-control-your-texture-units/
//https://www.opengl.org/discussion_boards/showthread.php/163092-Passing-Multiple-Textures-from-OpenGL-to-GLSL-shader
//https://en.wikibooks.org/wiki/OpenGL_Programming/Advanced/GLSL

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
	


	GLuint program = Renderer::shaderManager().currentProgram();
	Renderer::shaderManager().useProgram(_shader);
	
	if (_material){
		// Diffuse binding
		GLint diffuse = glGetUniformLocation(program, "uniform_diffuse");

		if (_material->diffuse && diffuse != -1){
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, _material->diffuse);
			Renderer::shaderManager().uniform(diffuse, 0);
		}

		// Specular binding
		GLint specular = glGetUniformLocation(program, "uniform_specular");

		if (_material->specular && specular != -1){
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, _material->specular);
			Renderer::shaderManager().uniform(specular, 1);
		}

		// Normal binding
		GLint normal = glGetUniformLocation(program, "uniform_normal");

		if (_material->normal && normal != -1){
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, _material->normal);
			Renderer::shaderManager().uniform(normal, 2);
		}


		Entity* lightPosition = EntityManager::getEntity("player");

		//Entity* camera = EntityManager::getEntity("camera");

		if (lightPosition){
			glm::vec3 position = lightPosition->getComponent<Transform>()->position();

			position.z = -position.z;

			glm::vec3 difference = position - _transform->position();


			glm::vec3 direction = glm::normalize(difference);

			direction = glm::normalize(direction * _transform->rotation());

			Renderer::shaderManager().attribute("in_lightDirection", direction);

			float distance = glm::distance(position, _transform->position());

			float maxDistance = 1024;

			distance = clamp(0, 1, changeRange(0, maxDistance, 1, 0, distance));

			Renderer::shaderManager().attribute("in_lightDistance", distance);
		}

		Renderer::shaderManager().uniform("uniform_resolution", Renderer::window().size());

		//GLint light = glGetAttribLocation(program, "in_light");
		//
		//if (light != -1){
		//	Renderer::shaderManager().uniform(light, glm::vec3(0, 0, 0));
		//}
	}
	else{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	bool switched = false;

	if (glIsEnabled(GL_LIGHTING) && _unlit){
		switched = true;
		glDisable(GL_LIGHTING);
	}

	draw();

	glPopMatrix();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, 0);

	Renderer::shaderManager().useProgram(program);

	if (switched && _unlit)
		glEnable(GL_LIGHTING);
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