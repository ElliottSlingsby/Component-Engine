#include "Playing.hpp"

#include <Static\Renderer.hpp>

#include <Component\Box2d.hpp>
#include <Component\Circle2d.hpp>
#include <Component\Camera.hpp>
#include <Component\Debug\Axis.hpp>
#include <Component\Debug\Grid.hpp>

#include <Utils.hpp>

#include "Movement.hpp"
#include "Velocity.hpp"
#include "Input.hpp"
#include "Brain.hpp"
#include "Feeder.hpp"
#include "Vision.hpp"

#include "Log.hpp"

void Playing::setTraining(bool training){
	_training = training;
}

void Playing::setSize(const glm::vec2& size){
	_size = size;
}

void Playing::setResolution(const glm::vec2& resolution){
	_resolution = resolution;
}

void Playing::setError(float error){
	_error = error;
}

void Playing::setOffline(bool offline){
	_offline = offline;
}

void Playing::on(){
	if (!_training && !_offline){
		const unsigned int layers = 3;
		const unsigned int inputs = _resolution.x * _resolution.y;
		const unsigned int hiddenNeurons = 3;
		const unsigned int outputs = 2;

		FANN::neural_net network;

		network.create_standard(layers, inputs, hiddenNeurons, outputs);

		network.set_activation_function_hidden(FANN::SIGMOID_SYMMETRIC);
		network.set_activation_function_output(FANN::SIGMOID_SYMMETRIC);

		const unsigned int maxEpochs = 1000;
		const unsigned int epochsBetweenReports = 100;

		network.train_on_file("../data/log.txt", maxEpochs, epochsBetweenReports, _error);

		network.save("../data/log.net");

		network.destroy();
	}

	
	Entity* origin = EntityManager::createEntity("origin");
	origin->getComponent<Transform>()->setPosition(glm::vec3(0, 0, 1));
	origin->addComponent(new Grid(512, 128, 8, Grid::AxisZ));
	origin->addComponent(new Camera);
	origin->getComponent<Camera>()->set2d(true);
	origin->getComponent<Camera>()->setZoom(20.f);
	
	Entity* player = EntityManager::createEntity("player");
	player->getComponent<Transform>()->setRotation(glm::quat(glm::vec3(glm::radians(90.f), 0, 0)));
	player->addComponent(new Velocity(1.25f));
	player->addComponent(new Input);
	player->addComponent(new Movement(25000.f, true));
	player->addComponent(new Axis(256.f, false));
	player->addComponent(new Circle2d(256.f));
	player->addComponent(new Feeder(2.f, 10.f, 100.f));
	player->addComponent(new Vision(_size, _resolution));
	player->addComponent(new Brain(_training));

	int amount;

	if (_training)
		amount = 3;
	else
		amount = 10;

	for (int i = 0; i < amount; i++){
		Entity* computer = EntityManager::createEntity("computer");
		computer->getComponent<Transform>()->setRotation(glm::quat(glm::vec3(glm::radians(90.f), 0, glm::radians(randomRange(360, 1)))));
		computer->getComponent<Transform>()->setPosition(glm::vec3(randomRange(_width, _spread), randomRange(_height, _spread), 0));
		computer->addComponent(new Circle2d(256.f));
		computer->addComponent(new Velocity(1.25f));
		computer->addComponent(new Movement(25000.f));
		computer->addComponent(new Axis(256.f, false));
		computer->addComponent(new Feeder(2.f, 10.f, 100.f));
		computer->addComponent(new Brain(_training));
		computer->addComponent(new Vision(_size, _resolution));
	}

	EntityManager::invokeAll(Entity::TRIGGER_LOAD);
}

void Playing::off(){
	EntityManager::destroyAll();
	EntityManager::deleteDestroyed();
}