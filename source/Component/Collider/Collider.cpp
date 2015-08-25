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
		printf("IT'S A SPHERE!\n");
		return true;
	}

	Box* box = dynamic_cast<Box*>(other);

	if (box){
		printf("IT'S A BOX!\n");
		return true;
	}

	return false;
}