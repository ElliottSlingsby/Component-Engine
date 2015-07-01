#pragma once

#include <Base\HelperComponent.hpp>
#include <Component\Transform.hpp>

class Input : public HelperComponent{
	Transform* _transform = 0;

	bool _moveLeft = false;
	bool _moveRight = false;
	bool _moveForward = false;
	bool _moveBack = false;

public:
	void load(){
		_transform = _getComponent<Transform>();
	}

	void input(SDL_Event& evnt){
		if (evnt.type == SDL_KEYDOWN){
			switch (evnt.key.keysym.sym){

			case SDLK_LEFT:
				_moveLeft = true;
				break;
			case SDLK_RIGHT:
				_moveRight = true;
				break;
			case SDLK_UP:
				_moveForward = true;
				break;
			case SDLK_DOWN:
				_moveBack = true;
				break;
			}
		}
		else if (evnt.type == SDL_KEYUP){
			switch (evnt.key.keysym.sym){

			case SDLK_LEFT:
				_moveLeft = false;
				break;
			case SDLK_RIGHT:
				_moveRight = false;
				break;
			case SDLK_UP:
				_moveForward = false;
				break;
			case SDLK_DOWN:
				_moveBack = false;
				break;
			}
		}
	}

	void update(long dt){
		if (_moveLeft)
			_transform->translate(Vector3f(0.01f, 0.f, 0.f));

		if (_moveRight)
			_transform->translate(Vector3f(-0.01f, 0.f, 0.f));

		if (_moveForward)
			_transform->translate(Vector3f(0.f, 0.f, 0.01f));

		if (_moveBack)
			_transform->translate(Vector3f(0.f, 0.f, -0.01f));
	}

	Component* clone(){
		return new Input;
	}
};