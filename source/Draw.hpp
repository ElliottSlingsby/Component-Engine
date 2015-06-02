#pragma once

#include "Component.hpp"

struct Draw : public Component{
	Draw(){}

	Component* clone(){
		return new Draw;
	}

	void render(Renderer* renderer){
		renderer->renderTest();
	}
};