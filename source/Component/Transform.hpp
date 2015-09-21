#pragma once

#include <Entity\Component.hpp>
#include <glm\vec3.hpp>
#include <glm\gtc\quaternion.hpp>
#include <set>
#include <vector>

typedef std::vector<int> intVector;

class Transform : public Component{
	Transform* _parent = 0;

	typedef std::set<Transform*> TransformSet;
	TransformSet _children;

	glm::vec3 _position;
	glm::quat _rotation;
	glm::vec3 _scale;

	void _addChild(Transform* child);
	void _removeChild(Transform* child);

public:
	Transform(
		const glm::vec3& position = glm::vec3(0.f, 0.f, 0.f),
		const glm::quat& rotation = glm::quat(1.f, 0.f, 0.f, 0.f),
		const glm::vec3& scale = glm::vec3(1.f, 1.f, 1.f)
	);

	~Transform();

	// Getters
	Transform* parent();
	void childrenIDs(intVector& intVector);

	glm::vec3 position();
	glm::quat rotation();
	glm::vec3 scale();

	unsigned int childrenSize();

	// Setters
	void setParent(Transform* parent);
	void setPosition(const glm::vec3& vector);
	void setRotation(const glm::quat& vector);
	void setScale(const glm::vec3& scale);

	// Global movements
	void translate(const glm::vec3& vector);
	void rotate(const glm::quat& rotation);

	// Local movements
	void localTranslate(const glm::vec3& translation);
	void localRotate(const glm::quat& rotation);

	// Look methods
	void lookAt(const glm::vec3& position);
	glm::vec3 lookingAt();
};