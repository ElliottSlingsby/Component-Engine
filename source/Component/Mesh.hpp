#pragma once

#include "Base\HelperComponent.hpp"
#include <GL\glew.h>
#include "Material.hpp"
#include "AssetLoader.hpp"

// While there's no obj loader, models have to be hardcoded. This will be changed eventually.

class Mesh : public HelperComponent{
protected:
	Transform* _transform = 0;
	GLuint mesh = 0;

public:
	void load(){
		_transform = _getComponent<Transform>();

		//mesh = AssetLoader::getAsset("torus.obj");
	}

	Component* clone(){
		return new Mesh;
	}

	void render(){
		glMatrixMode(GL_MODELVIEW);

		glPushMatrix();

		// Translate based on Transform
		glTranslatef(_transform->position().x(), 0.f, 0.f);
		glTranslatef(0.f, _transform->position().y(), 0.f);
		glTranslatef(0.f, 0.f, _transform->position().z());

		// Rotate based on Transform
		glRotatef(_transform->rotation().x(), 1.f, 0.f, 0.f);
		glRotatef(_transform->rotation().y(), 0.f, 1.f, 0.f);
		glRotatef(_transform->rotation().z(), 0.f, 0.f, 1.f);


		// Check to see if entity has a material
		Material* material = _getComponent<Material>();

		if (material)
			material->use();
		else
			// If not then use blank
			glBindTexture(GL_TEXTURE_2D, 0);

		// Testing cube

		//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, 0);

		glBegin(GL_QUADS);

		//Top
		glNormal3f(0.f, 1.f, 0.f);
		glTexCoord2f(1.f, 1.f);
		glVertex3f(-1.f, 1.f, 1.f);
		glTexCoord2f(1.f, 0.f);
		glVertex3f(1.f, 1.f, 1.f);
		glTexCoord2f(0.f, 0.f);
		glVertex3f(1.f, 1.f, -1.f);
		glTexCoord2f(0.f, 1.f);
		glVertex3f(-1.f, 1.f, -1.f);
		
		//Bottom
		glNormal3f(0.f, -1.f, 0.f);
		glTexCoord2f(0.f, 1.f);
		glVertex3f(-1.f, -1.f, -1.f);
		glTexCoord2f(0.f, 0.f);
		glVertex3f(1.f, -1.f, -1.f);
		glTexCoord2f(1.f, 0.f);
		glVertex3f(1.f, -1.f, 1.f);
		glTexCoord2f(1.f, 1.f);
		glVertex3f(-1.f, -1.f, 1.f);
		
		//Front
		glNormal3f(0.f, 0.f, 1.f);
		glTexCoord2f(1.f, 1.f);
		glVertex3f(-1.f, -1.f, 1.f);
		glTexCoord2f(1.f, 0.f);
		glVertex3f(1.f, -1.f, 1.f);
		glTexCoord2f(0.f, 0.f);
		glVertex3f(1.f, 1.f, 1.f);
		glTexCoord2f(0.f, 1.f);
		glVertex3f(-1.f, 1.f, 1.f);
				
		
		//Back
		glNormal3f(0.f, 0.f, -1.f);
		glTexCoord2f(0.f, 1.f);
		glVertex3f(-1.f, 1.f, -1.f);
		glTexCoord2f(0.f, 0.f);
		glVertex3f(1.f, 1.f, -1.f);
		glTexCoord2f(1.f, 0.f);
		glVertex3f(1.f, -1.f, -1.f);
		glTexCoord2f(1.f, 1.f);
		glVertex3f(-1.f, -1.f, -1.f);
		
		//Left
		glNormal3f(-1.f, 0.f, 0.f);
		glTexCoord2f(1.f, 1.f);
		glVertex3f(-1.f, -1.f, -1.f);
		glTexCoord2f(1.f, 0.f);
		glVertex3f(-1.f, -1.f, 1.f);
		glTexCoord2f(0.f, 0.f);
		glVertex3f(-1.f, 1.f, 1.f);
		glTexCoord2f(0.f, 1.f);
		glVertex3f(-1.f, 1.f, -1.f);
				
		
		//Right
		glNormal3f(1.f, 0.f, 0.f);
		glTexCoord2f(0.f, 1.f);
		glVertex3f(1.f, 1.f, -1.f);
		glTexCoord2f(0.f, 0.f);
		glVertex3f(1.f, 1.f, 1.f);
		glTexCoord2f(1.f, 0.f);
		glVertex3f(1.f, -1.f, 1.f);
		glTexCoord2f(1.f, 1.f);
		glVertex3f(1.f, -1.f, -1.f);

		glEnd();

		glPopMatrix();
	}
};