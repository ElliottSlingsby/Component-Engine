#include "Box3d.hpp"

#include <GL\glew.h>

Box3d::Box3d(float width, float height, float depth) : Collider(BOX3D){
	_size = Vec3(width, height, depth);
}

void Box3d::load(){
	_transform = getComponent<Transform>();
}

void Box3d::_update(){
	// Updating this world coordinates for each corner
	Vec3 half = (_size * _transform->scale()) / 2.f;

	_corners[0] = _transform->apply(Vec3(-half.x, -half.y, -half.z));
	_corners[1] = _transform->apply(Vec3(half.x, -half.y, -half.z));
	_corners[2] = _transform->apply(Vec3(half.x, half.y, -half.z));
	_corners[3] = _transform->apply(Vec3(-half.x, half.y, -half.z));

	_corners[4 + 0] = _transform->apply(Vec3(-half.x, -half.y, half.z));
	_corners[4 + 1] = _transform->apply(Vec3(half.x, -half.y, half.z));
	_corners[4 + 2] = _transform->apply(Vec3(half.x, half.y, half.z));
	_corners[4 + 3] = _transform->apply(Vec3(-half.x, half.y, half.z));
		
	// Updating this axes rotation
	_axes[0] = Vec3(1, 0, 0);
	_axes[1] = Vec3(0, 1, 0);
	_axes[2] = Vec3(0, 0, 1);

	Quat rotation = _transform->rotation();
		
	for (int i = 0; i < 3; i++){
		Vec3 axis = rotation * _axes[i];
		_axes[i] = axis;
	}
}

void Box3d::render(){
	_update();
	
	if (_testColliding)
		glColor3f(1.f, 1.f, 0.f);
	else
		glColor3f(1.f, 1.f, 1.f);
	
	// Quads
	glBegin(GL_QUADS);

	// Draw top
	for (int i = 3; i >= 0; i--){
		glVertex3fv(&_corners[i].x);
	}

	// Draw bottom
	for (int i = 0; i < 4; i++){
		glVertex3fv(&_corners[4 + i].x);
	}

	// Draw 4 sides
	for (int i = 0; i < 4; i++){
		glVertex3f(_corners[i].x, _corners[i].y, _corners[i].z);
		glVertex3f(_corners[(1 + i) % 4].x, _corners[(1 + i) % 4].y, _corners[(1 + i) % 4].z);
		glVertex3f(_corners[4 + (1 + i) % 4].x, _corners[4 + (1 + i) % 4].y, _corners[4 + (1 + i) % 4].z);
		glVertex3f(_corners[4 + i].x, _corners[4 + i].y, _corners[4 + i].z);
	}

	glEnd();

	glLineWidth(3);
	glColor3f(0.f, 0.f, 0.f);

	// Lines
	glBegin(GL_LINE_STRIP);

	// Draw top
	for (int i = 3; i >= 0; i--){
		glVertex3fv(&_corners[i].x);
	}

	glEnd();

	glBegin(GL_LINE_STRIP);

	// Draw bottom
	for (int i = 0; i < 4; i++){
		glVertex3fv(&_corners[4 + i].x);
	}

	glEnd();

	// Draw 4 sides
	for (int i = 0; i < 4; i++){
		glBegin(GL_LINE_STRIP);

		glVertex3f(_corners[i].x, _corners[i].y, _corners[i].z);
		glVertex3f(_corners[(1 + i) % 4].x, _corners[(1 + i) % 4].y, _corners[(1 + i) % 4].z);
		glVertex3f(_corners[4 + (1 + i) % 4].x, _corners[4 + (1 + i) % 4].y, _corners[4 + (1 + i) % 4].z);
		glVertex3f(_corners[4 + i].x, _corners[4 + i].y, _corners[4 + i].z);

		glEnd();
	}

	glEnd();

	glLineWidth(1);
	glColor3f(1.f, 1.f, 1.f);
	
	_testColliding = false;
}

bool Box3d::overlapping(const Vec2& first, const Vec2& second){
	if (first.x <= second.x && first.y >= second.x)
		return true;
	if (first.x <= second.y && first.y >= second.y)
		return true;
	if (second.x <= first.x && second.y >= first.x)
		return true;
	if (second.x <= first.y && second.y >= first.y)
		return true;

	return false;
}

bool Box3d::isCollidingSystem(Collider* other){
	if (other->type == Collider::BOX3D){
		Box3d* otherBox = static_cast<Box3d*>(other);
		return isColliding(otherBox);
	}

	return false;
}

bool Box3d::isColliding(Box3d* other, bool recurse){
	_update();

	// Projecting other onto this axes and updating magnitudes
	Box3d* targets[2] = { this, other };
	
	for (int y = 0; y < 2; y++){
		for (int x = 0; x < 3; x++){
			float minimum = dot(_axes[x], targets[y]->_corners[0]);
			float maximum = minimum;
	
			for (int i = 0; i < 8; i++){
				float magnitude = dot(_axes[x], targets[y]->_corners[i]);
	
				if (magnitude < minimum)
					minimum = magnitude;
				else if (magnitude > maximum)
					maximum = magnitude;
			}
	
			_magnitudes[y * 3 + x] = Vec2(minimum, maximum);
		}
	}
	


	// Check for exit case before carrying on
	if (recurse){
		bool result = other->isColliding(this, false);
	
		if (!result)
			return false;
	}
	


	// Check for overlaps
	for (int i = 0; i < 3; i++){
		if (!overlapping(_magnitudes[i], _magnitudes[3 + i]))
			return false;
	}

	if (recurse)
		return true;





	// Edge axes update
	for (int y = 0; y < 3; y++){
		for (int x = 0; x < 3; x++){
			_edgeAxes[y * 3 + x] = cross(_axes[x], other->_axes[y]);
		}
	}	

	// Edge calculations
	for (int x = 0; x < 2; x++){
		for (int y = 0; y < 9; y++){
			float minimum = dot(_edgeAxes[y], targets[x]->_corners[0]);
			float maximum = minimum;

			for (int i = 0; i < 8; i++){
				float magnitude = dot(_edgeAxes[y], targets[x]->_corners[i]);

				if (magnitude < minimum)
					minimum = magnitude;
				else if (magnitude > maximum)
					maximum = magnitude;
			}

			_edgeMagnitudes[x * 9 + y] = Vec2(minimum, maximum);
		}
	}

	for (int i = 0; i < 9; i++){
		if (!overlapping(_edgeMagnitudes[i], _edgeMagnitudes[9 + i]))
			return false;
	}

	return true;
}

void Box3d::onCollision(int id){
	_testColliding = true;
}