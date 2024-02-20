#include "ECS.h"

HashMap<const char*, ComponentId>* ECS::componentRegistry = new HashMap<const char*, ComponentId>(32);

ECS::ECS(){
    logger = new Logger("ECS");
    entityManager = new EntityManager(100);
    archetypeRegistry = new HashMap<ArchetypeId,Archetype*>(50);
}

ECS::~ECS(){
    if (componentRegistry->getSize() != 0) {
        logger->warn("%d component types have not been unregistered.",componentRegistry->getSize());
    }

    delete componentRegistry;
    delete entityManager;
    delete logger;
}

EntityId ECS::createEntity(){
    return entityManager->createEntity();
}

void ECS::destroyEntity(EntityId entity){
    entityManager->destroyEntity(entity);
}