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






	//const unsigned int layers = 3;
	//const unsigned int inputs = 5 * 5;
	//const unsigned int hiddenNeurons = 3;
	//const unsigned int outputs = 2;
	//
	//FANN::neural_net network;
	//
	//network.create_standard(layers, inputs, hiddenNeurons, outputs);
	//
	//network.set_activation_function_hidden(FANN::SIGMOID_SYMMETRIC);
	//network.set_activation_function_output(FANN::SIGMOID_SYMMETRIC);
	//
	//const unsigned int maxEpochs = 10000;
	//const unsigned int epochsBetweenReports = 100;
	//const float error = (const float)0.00001;
	//
	//network.train_on_file("../data/log.txt", maxEpochs, epochsBetweenReports, error);
	//
	//network.save("../data/log.net");
	//
	//network.destroy();













	EntityManager::stateMachine().addState(new Playing);
	EntityManager::stateMachine().changeState<Playing>();
	
	return true;
}