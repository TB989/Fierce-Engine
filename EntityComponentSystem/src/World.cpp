#include "World.h"

World::World(){
	//Init ECS
	entityManager = new EntityManager(50);
	componentManager = new ComponentManager();
	//componentManager->registerComponent<Transform2D>(50);
}

World::~World(){

	//Delete ECS
	//componentManager->unregisterComponent<Transform2D>();
	delete componentManager;
	delete entityManager;
}