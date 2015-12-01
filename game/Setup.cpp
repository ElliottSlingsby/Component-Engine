#include <Setup.hpp>

#include "Playing.hpp"
#include <floatfann.h>
#include <fann_cpp.h>

bool setup(int argc, char *args[]){
	srand((unsigned int)time(0));

	Renderer::window().setSize(1280, 720);
	Renderer::window().setFixedMouse(true);

	AssetLoader::setAssetLocation("data/assets");
	Renderer::shaderManager().setShaderLocation("data/shaders");

	if (!Renderer::initiate())
		return false;

#ifdef _DEBUG
	Renderer::console().setRunning(true);
#endif

	EntityManager::stateMachine().addState(new Playing);
	EntityManager::stateMachine().changeState<Playing>();



	const unsigned int layers = 3;
	const unsigned int inputs = 2;
	const unsigned int hiddenNeurons = 3;
	const unsigned int outputs = 3;
	
	FANN::neural_net network;

	network.create_standard(layers, inputs, hiddenNeurons, outputs);

	network.set_activation_function_hidden(FANN::SIGMOID_SYMMETRIC);
	network.set_activation_function_output(FANN::SIGMOID_SYMMETRIC);

	const unsigned int maxEpochs = 500000;
	const unsigned int epochsBetweenReports = 1000;
	const float error = (const float) 0.001;

	network.train_on_file("../data/simple_training.txt", maxEpochs, epochsBetweenReports, error);

	network.save("../data/simple_training.net");

	network.destroy();
	
	return true;
}