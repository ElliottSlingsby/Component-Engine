#pragma once

#include <Static\EntityManager.hpp>

class Playing: public State{
	int _spread = 5;
	int _width = 4096;
	int _height = 2048;

	bool _training = true;
	bool _offline = false;
	glm::vec2 _size = glm::vec2(2048, 2048);
	glm::vec2 _resolution = glm::vec2(5, 5);
	float _error;

public:
	void on();
	void off();

	void setOffline(bool offline);
	void setTraining(bool training);
	void setSize(const glm::vec2& size);
	void setResolution(const glm::vec2& resolution);
	void setError(float error);
};