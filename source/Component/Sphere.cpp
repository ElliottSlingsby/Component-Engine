#include "Sphere.hpp"

#include "Box.hpp"

glm::vec3 Sphere::_position(){
	return _transform->position() - _offset;
}

Sphere::Sphere(float radius, bool inverted, const glm::vec3& offset) : Collider(COLLIDER_SPHERE, inverted){
	_radius = radius;
	_offset = _offset;
}

bool Sphere::isColliding(Collider* other){
	Box* box = dynamic_cast<Box*>(other);

	if (box){
		return false;
	}

	Sphere* sphere = dynamic_cast<Sphere*>(other);

	if (sphere){
		float length = (float)((position() - sphere->position()).length());

		if (sphere->_inverted && _inverted)
			return false;

		if (!_inverted && !sphere->_inverted){
			if (length - sphere->_radius <= _radius)
				return true;

			return false;
		}
		else if (_inverted){
			if (length + sphere->_radius <= _radius)
				return false;

			return true;
		}
		else if (sphere->_inverted){
			if (length + _radius <= sphere->_radius)
				return false;

			return true;
		}
	}

	return false;
}

void Sphere::setRadius(float radius){
	_radius = radius;
}

void Sphere::setOffset(const glm::vec3& offset){
	_offset = offset;
}