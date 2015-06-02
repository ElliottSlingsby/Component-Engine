#pragma once

#include "Component.hpp"
#include "Vector3.hpp"

struct Draw : public Component{
	Draw(){}

	Component* clone(){
		return new Draw;
	}

	void render(Renderer* renderer){
		renderer->drawTriangle(
			Vector3f(1.f, 0.f, 0.f), 
			Vector3f(0.f, 1.f, 0.f),
			Vector3f(0.f, 0.f, 1.f)
		);
	}
};