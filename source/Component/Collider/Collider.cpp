#include "Collider.hpp"

bool Box::isColliding(Collider* other){
	Box* box = dynamic_cast<Box*>(other);

	if (box){
		printf("IT'S A BOX!\n");
		return true;
	}

	Sphere* sphere = dynamic_cast<Sphere*>(other);

	if (sphere){
		printf("IT'S A SPHERE!\n");
		return true;
	}

	return false;
}

bool Sphere::isColliding(Collider* other){
	Sphere* sphere = dynamic_cast<Sphere*>(other);

	if (sphere){
		float length = (position() - sphere->position()).length();

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

	//Box* box = dynamic_cast<Box*>(other);

	//if (box){
	//	printf("IT'S A BOX!\n");
	//	return true;
	//}

	return false;
}