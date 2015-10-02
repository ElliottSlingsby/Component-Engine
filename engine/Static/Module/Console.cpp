#include "Console.hpp"

#include <iostream>
#include <Static\EntityManager.hpp>
#include <Static\Renderer.hpp>
#include <Static\AssetLoader.hpp>

#include <Component\Debug\Line.hpp>

using namespace Module;

static int consoleThread(void* data){
	Console& console = *static_cast<Console*>(data);

	while (console.running()){
		std::string input = console.getInput();
		console.feedInput(input);
	}

	return 0;
}

Console::Console(){
	_patternMap["null"] = std::regex("^ *$", std::regex_constants::basic);
	_patternMap["exit"] = std::regex("^(?:exit|quit|close)$", std::regex_constants::icase);
	_patternMap["help"] = std::regex("^help *(\\S*) *$", std::regex_constants::icase | std::regex_constants::ECMAScript);
	_patternMap["hello"] = std::regex("^(?:hello|hey|hi)(?: +.*$|$)", std::regex_constants::icase);
	_patternMap["you"] = std::regex("^(?:you|yourself)$", std::regex_constants::icase);
	_patternMap["position"] = std::regex("^(?:position|pos|move) +(\\S+) +([-+]?(?:[0-9]*\\.[0-9]+|[0-9]+)) +([-+]?(?:[0-9]*\\.[0-9]+|[0-9]+)) +([-+]?(?:[0-9]*\\.[0-9]+|[0-9]+))$", std::regex_constants::icase | std::regex_constants::ECMAScript);
	_patternMap["rotation"] = std::regex("^(?:rotation|rotate|turn) +(\\S+) +([-+]?(?:[0-9]*\\.[0-9]+|[0-9]+)) +([-+]?(?:[0-9]*\\.[0-9]+|[0-9]+)) +([-+]?(?:[0-9]*\\.[0-9]+|[0-9]+))$", std::regex_constants::icase | std::regex_constants::ECMAScript);
	_patternMap["scale"] = std::regex("^(?:scale|size) +(\\S+) +([-+]?(?:[0-9]*\\.[0-9]+|[0-9]+)) +([-+]?(?:[0-9]*\\.[0-9]+|[0-9]+)) +([-+]?(?:[0-9]*\\.[0-9]+|[0-9]+))$", std::regex_constants::icase | std::regex_constants::ECMAScript);
	_patternMap["delete"] = std::regex("^(?:delete|kill|destroy|remove|rm) +(\\S+) *$", std::regex_constants::icase | std::regex_constants::ECMAScript);
	_patternMap["list"] = std::regex("^(?:list|ls|entities|ents)$", std::regex_constants::icase);
	_patternMap["reload"] = std::regex("^(?:reload|reset)$", std::regex_constants::icase);
	_patternMap["draw"] = std::regex("^(?:draw|line) +(\\S+) +([-+]?(?:[0-9]*\\.[0-9]+|[0-9]+)) +([-+]?(?:[0-9]*\\.[0-9]+|[0-9]+)) +([-+]?(?:[0-9]*\\.[0-9]+|[0-9]+))$", std::regex_constants::icase | std::regex_constants::ECMAScript);
	_patternMap["cross"] = std::regex("^cross +(\\S+) +(\\S+) +(\\S+)$", std::regex_constants::icase | std::regex_constants::ECMAScript);
	_patternMap["dot"] = std::regex("^dot +(\\S+) +(\\S+)$", std::regex_constants::icase | std::regex_constants::ECMAScript);
}

void Console::setPrefix(const std::string& prefix){
	_prefix = prefix;
}

std::string Console::getInput(){
	if (_prefix != "")
		std::cout << _prefix << " ";

	std::string input;

	std::getline(std::cin, input);

	return input;
}

void Console::feedInput(const std::string& input){
	_input = input;
}

int Console::interpretInput(){
	std::string input = _input;

	_input = "";

	std::smatch results;

	if (std::regex_match(input, results, _patternMap["null"])){
		return NULL_CODE;
	}
	else if (std::regex_match(input, results, _patternMap["exit"])){
		_running = false;
		return EXIT_CODE;
	}
	else if (std::regex_match(input, results, _patternMap["help"])){
		std::smatch subResults;

		if (std::regex_match(results[1].str(), subResults, _patternMap["you"]))
			std::cout << "I don't want to do that." << std::endl;
		else if (results[1].str() != "")
			std::cout << "I can't help " << results[1].str() << "." << std::endl;
		else
			std::cout << "Help who?" << std::endl;

		return VALID_CODE;
	}
	else if (std::regex_match(input, results, _patternMap["position"])){
		Entity* entity = EntityManager::getEntity(results[1].str());

		if (entity)
			entity->getComponent<Transform>()->setPosition(glm::vec3(std::stof(results[2].str()), std::stof(results[3].str()), std::stof(results[4].str())));

		return VALID_CODE;
	}
	else if (std::regex_match(input, results, _patternMap["rotation"])){
		Entity* entity = EntityManager::getEntity(results[1].str());

		if (entity)
			entity->getComponent<Transform>()->setRotation(glm::quat(glm::vec3(glm::radians(std::stof(results[2].str())),glm::radians(std::stof(results[3].str())),glm::radians(std::stof(results[4].str())))));

		return VALID_CODE;
	}
	else if (std::regex_match(input, results, _patternMap["scale"])){
		Entity* entity = EntityManager::getEntity(results[1].str());

		if (entity)
			entity->getComponent<Transform>()->setScale(glm::vec3(std::stof(results[2].str()), std::stof(results[3].str()), std::stof(results[4].str())));

		return VALID_CODE;
	}
	else if (std::regex_match(input, results, _patternMap["delete"])){
		EntityManager::destroyEntities(results[1].str());

		return VALID_CODE;
	}
	else if (std::regex_match(input, results, _patternMap["list"])){
		IntVector ids;
		EntityManager::getEntities(ids);

		for (IntVector::iterator i = ids.begin(); i != ids.end(); i++)
			std::cout << *i << " : " << EntityManager::NameBank().getName(*i) << std::endl;

		return VALID_CODE;
	}
	else if (std::regex_match(input, results, _patternMap["draw"])){
		Entity* line = EntityManager::createEntity(results[1].str());

		if (line)
			line->addComponent(new Line(glm::vec3(std::stof(results[2].str()), std::stof(results[3].str()), std::stof(results[4].str()))));

		line->trigger(Entity::TRIGGER_LOAD);

		return VALID_CODE;
	}
	else if (std::regex_match(input, results, _patternMap["cross"])){
		Entity* entityFirst = EntityManager::getEntity(results[1].str());
		Entity* entitySecond = EntityManager::getEntity(results[2].str());

		if (entityFirst && entitySecond){
			Line* lineFirst = entityFirst->getComponent<Line>();
			Line* lineSecond = entitySecond->getComponent<Line>();

			if (lineFirst && lineSecond){
				Entity* line = EntityManager::createEntity(results[3].str());

				if (line){
					glm::vec3 cross = glm::cross(glm::normalize(lineFirst->vector()), glm::normalize(lineSecond->vector()));

					line->addComponent(new Line(cross * 10.f));
					line->trigger(Entity::TRIGGER_LOAD);

					return VALID_CODE;
				}
			}
		}

		return INVALID_CODE;
	}
	else if (std::regex_match(input, results, _patternMap["dot"])){
		Entity* entityFirst = EntityManager::getEntity(results[1].str());
		Entity* entitySecond = EntityManager::getEntity(results[2].str());

		if (entityFirst && entitySecond){
			Line* lineFirst = entityFirst->getComponent<Line>();
			Line* lineSecond = entitySecond->getComponent<Line>();

			float length = glm::dot(glm::normalize(lineFirst->vector()), glm::normalize(lineSecond->vector()));

			lineSecond->setVector(lineSecond->vector() * length);

			return VALID_CODE;
		}

		return INVALID_CODE;
	}
	else if (std::regex_match(input, results, _patternMap["reload"])){
		EntityManager::StateMachine().reload();

		return VALID_CODE;
	}
	else if (std::regex_match(input, results, _patternMap["hello"])){
		std::cout << "Hello." << std::endl;
		return VALID_CODE;
	}
	std::cout << "I don't understand." << std::endl;

	return INVALID_CODE;
}

void Console::setRunning(bool running){
	_running = running;

	if (running && !_thread)
		_thread = SDL_CreateThread(consoleThread, "console", this);
	else if (!running && _thread)
		SDL_WaitThread(_thread, 0);
}

bool Console::running(){
	return _running;
}