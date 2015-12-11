#include <Static\EntityManager.hpp>
#include <algorithm>
#include <Component\Circle2d.hpp>

#include <Utils.hpp>

int _spread = 5;
int _width = 4096;
int _height = 2048;


// Should really be a component system
void runCollisions(){
	Entity* player = EntityManager::getEntity("player");

	EntityVector computers;
	EntityVector food;

	EntityManager::getEntities("computer", computers);
	EntityManager::getEntities("food", food);

	if (food.size() != 25){



		Entity* test = EntityManager::createEntity("food");
		test->getComponent<Transform>()->setRotation(glm::quat(glm::vec3(glm::radians(90.f), 0, 0)));
		test->getComponent<Transform>()->setPosition(glm::vec3(randomRange(_width, _spread), randomRange(_height, _spread), 0));
		test->addComponent(new Circle2d(128.f));
		test->trigger(Entity::TRIGGER_LOAD);

		//EntityManager::stateMachine().reload();
		//return;
	}

	EntityVector all;

	if (player)
		all.reserve(1 + computers.size() + food.size());
	else
		all.reserve(computers.size() + food.size());

	if (player)
		all.push_back(player);

	all.insert(all.end(), computers.begin(), computers.end());
	all.insert(all.end(), food.begin(), food.end());

	for (EntityVector::iterator checking = all.begin(); checking != all.end(); checking++){
		for (EntityVector::iterator other = all.begin(); other != all.end(); other++){
			if (checking == other)
				continue;

			Circle2d* checkingCircle = (*checking)->getComponent<Circle2d>();
			Circle2d* otherCircle = (*other)->getComponent<Circle2d>();

			if (checkingCircle->isColliding(otherCircle)){
				(*checking)->invoke(&Component::onCollision, (*other)->id());
				(*other)->invoke(&Component::onCollision, (*checking)->id());
			}
		}
	}
}