#pragma once

#include <Entity\Component.hpp>
#include <glm\vec3.hpp>
#include <glm\gtc\quaternion.hpp>

class Transform : public Component{
	glm::vec3 _position;
	glm::quat _rotation;
	glm::vec3 _scale;

public:
	Transform(
		const glm::vec3& position = glm::vec3(0.f, 0.f, 0.f),
		const glm::quat& rotation = glm::quat(1.f, 0.f, 0.f, 0.f),
		const glm::vec3& scale = glm::vec3(1.f, 1.f, 1.f)
	);

	// Getters
	glm::vec3 position();
	glm::quat rotation();
	glm::vec3 scale();

	// Setters
	void setPosition(const glm::vec3& vector);
	void setRotation(const glm::quat& vector);
	void setScale(const glm::vec3& scale);

	// Look methods
	void lookAt(const glm::vec3& position);
	glm::vec3 lookingAt();

	// Global movements
	void translate(const glm::vec3& vector);
	void rotate(const glm::quat& rotation);

	// Local movements
	void localTranslate(float speed, const glm::quat& offset = glm::quat(1.f, 0.f, 0.f, 0.f));
	void localRotate(const glm::quat& rotation);
};