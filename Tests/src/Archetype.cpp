#include "Archetype.h"

Archetype::Archetype(ArchetypeId id){
    archetypeId = id;
    numEntities = 0;
    componentVectors = new HashMap<const char*, IComponentVector*>(50);
}

Archetype::~Archetype(){
    delete componentVectors;
}

ArchetypeId Archetype::getId()
{
    return archetypeId;
}
