#pragma once

#include <Entity\Component.hpp>
#include <set>
#include <vector>

#include <Maths\Vec3.hpp>
#include <Maths\Quat.hpp>

typedef std::vector<int> IntVector;

class Transform : public Component{
	Transform* _parent = 0;

	typedef std::set<Transform*> TransformSet;
	TransformSet _children;

	Vec3 _position;
	Quat _rotation;
	Vec3 _scale;

	void _addChild(Transform* child);
	void _removeChild(Transform* child);

public:
	Transform(
		const Vec3& position = Vec3(0.f, 0.f, 0.f),
		const Quat& rotation = Quat(1.f, 0.f, 0.f, 0.f),
		const Vec3& scale = Vec3(1.f, 1.f, 1.f)
	);

	~Transform();

	// Getters
	Transform* parent();
	void childrenIDs(IntVector& intVector);

	Vec3 position();
	Quat rotation();
	Vec3 scale();
	Vec3 localPosition();
	Quat localRotation();

	unsigned int childrenSize();

	// Setters
	void setParent(Transform* parent);
	void setPosition(const Vec3& vector);
	void setRotation(const Quat& vector);
	void setScale(const Vec3& scale);

	Vec3 apply(const Vec3& vector);

	// Global movements
	void translate(const Vec3& vector);
	void rotate(Quat rotation);

	// Local movements
	void localTranslate(const Vec3& translation);
	void localRotate(const Quat& rotation);

	// Look methods
	void lookAt(const Vec3& position);
	Vec3 lookingAt();
};