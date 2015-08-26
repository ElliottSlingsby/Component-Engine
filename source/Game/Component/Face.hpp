#pragma once

#include "Entity\HelperComponent.hpp"
#include "Component\Model.hpp"
#include "Static\AssetLoader.hpp"

#include "..\State\Won.hpp"
#include "..\State\Lost.hpp"

class Face : public HelperComponent{
	Model* _model = 0;
	Transform* _transform = 0;

	float _maxHealth;
	float _health;
	float _hurtAmount;
	float _difficulty;

	float _faceTimer = 0.f;

	const MeshData* _idleMesh;
	const MeshData* _hurtMesh;

public:
	Face(float amount, float difficulty = 1.f,  float damage = 1.f){
		_maxHealth = amount;
		_health = amount;
		_hurtAmount = damage;
		_difficulty = difficulty;
	}

	void load(){
		_transform = getComponent<Transform>();

		_idleMesh = AssetLoader::getAsset<MeshData>("face_happy.obj");
		_hurtMesh = AssetLoader::getAsset<MeshData>("face_angry.obj");

		_model = getComponent<Model>();
	}

	void update(float dt){
		_faceTimer -= dt;
		
		if (_faceTimer < 0.f){
			if (_health > 1.f){
				_model->setMesh(_idleMesh);
				_faceTimer = 0.f;
			}
		}
		else{
			_model->setMesh(_hurtMesh);
		}

		_transform->push((150.f * _difficulty * ((_maxHealth - _health) / _maxHealth)) * dt);
	}

	void lateUpdate(){
		if (_health <= 0.f){
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
			_health -= _hurtAmount;
			other->destroy();
			_faceTimer = 2.f;
		}
		else if (other == EntityManager::getEntity("player")){
			other->destroy();
			EntityManager::changeState<Lost>();
		}
	}
};