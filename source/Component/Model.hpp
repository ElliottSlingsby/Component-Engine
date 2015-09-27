#pragma once

#include <Entity\HelperComponent.hpp>
#include <Static\AssetLoader.hpp>

class Model : public HelperComponent{
protected:
	Transform* _transform = 0;

	std::string _meshSrc = "";
	std::string _materialSrc = "";

	const MeshData* _mesh = 0;
	const MaterialData* _material = 0;

	bool _unlit = false;
	bool _fixedRotation = false;

public:
	Model(){}
	Model(const std::string& meshSrc, const std::string& materialSrc = "");

	void load();
	void render();

	// Draw calls
	virtual void draw();

	// Setters
	void setMesh(const MeshData* mesh);
	void setMaterial(const MaterialData* material);
	void setUnlit(bool unlit);
	void setFixedRotation(bool fixedRotation);
};