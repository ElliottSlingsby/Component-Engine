#include "Spawner.hpp"

Spawner::Spawner(){

}

Spawner::~Spawner(){

}

Spawner& Spawner::instance(){
	static Spawner instance;

	return instance;
}