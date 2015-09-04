#pragma once

#include "Entity\Component.hpp"
#include <glm\vec3.hpp>
#include <glm\gtc\quaternion.hpp>
//#include "Math\MathUtils.hpp"

class Transform : public Component{
	glm::vec3 _position;
	glm::quat _rotation;
	glm::vec3 _scale;

public:
	Transform(){
		_scale = glm::vec3(1.f, 1.f, 1.f);
	}

	Transform(glm::vec3 position, glm::quat rotation){
		_position = position;
		_rotation = rotation;
	}

	glm::vec3 position(){
		return _position;
	}

	glm::quat rotation(){
		return _rotation;
	}

	glm::vec3 scale(){
		return _scale;
	}

	void setPosition(glm::vec3 vector){
		_position = vector;
	}

	void setRotation(glm::quat vector){
		_rotation = vector;
	}

	void setScale(glm::vec3 scale){
		_scale = scale;
	}

	/*void lookAt(glm::vec3 position){
		position = position - _position;

		float yaw = atan2(position.x, position.z) * 180.f / (float)M_PI;

		float tmp = sqrt(pow(position.x, 2.f) + pow(position.z, 2.f));
		float pitch = atan2(tmp, position.y) * 180.f / (float)M_PI;

		_rotation = glm::vec3(-(pitch - 90.f), -yaw, 0.f);
	}

	glm::vec3 lookingAt(){
		return glm::vec3(
			cos(_rotation.y) * cos(_rotation.x),
			sin(_rotation.y) * cos(_rotation.x),
			sin(_rotation.x)			
		);
	}*/

	void translate(glm::vec3 vector){
		_position += vector;
	}

	void relativePush(float speed, glm::quat offset = glm::quat()){
		glm::vec3 vector(0.f, 0.f, 1.f);
		translate(_rotation * offset * vector);
	}

	void relativeRotate(glm::quat rotation){
		_rotation *= rotation;
	}

	void rotate(glm::quat rotation){
		_rotation = rotation * _rotation;
	}
};