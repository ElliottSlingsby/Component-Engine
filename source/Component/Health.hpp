#pragma once

#include "Entity\HelperComponent.hpp"
#include "State\Won.hpp"
#include "State\Lost.hpp"
#include "Component\Model\Model.hpp"
#include "Static\AssetLoader.hpp"

class Health : public HelperComponent{
	Model* _model = 0;

	float _amount;
	float _damage;

	float _timer = 0.f;

	const MeshData* _idleMesh;
	const MeshData* _hurtMesh;

public:
	Health(float amount, float damage = 1.f){
		_amount = amount;
		_damage = damage;
	}

	void load(){
		_idleMesh = AssetLoader::getAsset<MeshData>("face_happy.obj");
		_hurtMesh = AssetLoader::getAsset<MeshData>("face_angry.obj");

		_model = getComponent<Model>();
	}

	void update(float dt){
		_timer -= dt;
		
		if (_timer < 0.f){
			if (_amount > 1.f){
				_model->setMesh(_idleMesh);
				_timer = 0.f;
			}
		}
		else{
			_model->setMesh(_hurtMesh);
		}
	}

	void lateUpdate(){
		if (_amount <= 0.f){
			parent()->destroy();
			EntityManager::changeState<Won>();
		}

		Entity* entity = EntityManager::getEntity("player");

		if (entity)
			getComponent<Transform>()->lookAt(entity->getComponent<Transform>()->position());
	}

	void onCollision(int id){
		EntityVector bullets;
		EntityManager::getEntities("bullet", bullets);

		Entity* other = EntityManager::getEntity(id);

		if (!other)
			return;

		if (std::find(bullets.begin(), bullets.end(), other) != bullets.end()){
			_amount -= _damage;
			other->destroy();
			_timer = 0.5f;
		}
		else if (other == EntityManager::getEntity("player")){
			other->destroy();
			EntityManager::changeState<Lost>();
		}
	}
};