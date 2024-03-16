#pragma once

#include "Logger.h"
#include "Archetype.h"
#include "Types.h"

class System {
public:
	System() {
		logger = new Logger("SYSTEM");
		archetypeId = 0;
		numArchetypes = 0;
		archetypes= new Archetype*[10];
		for (int i = 0;i<10;i++) {
			archetypes[i] = nullptr;
		}
	}

	~System() {
		delete[] archetypes;
		delete logger;
	}

	void setComponentFlag(ComponentId componentId) {
		archetypeId |= (1 << componentId);
	}

	void clearArchetypes() {
		numArchetypes = 0;
		archetypes = new Archetype*[10];
		for (int i = 0; i < 10; i++) {
			archetypes[i] = nullptr;
		}
	}

	ArchetypeId getArchetypeSystemId() { return archetypeId; }

	void addArchetype(Archetype* archetype) {
		archetypes[numArchetypes] = archetype;
		numArchetypes++;
	}

	void removeArchetype(Archetype* archetype) {
		for (int i = 0; i < 10; i++) {
			if (archetypes[i]==archetype ) {
				archetypes[i] = archetypes[numArchetypes - 1];
				archetypes[numArchetypes - 1] = nullptr;
				numArchetypes--;
			}
		}
	}

	void uint32_to_binary(uint32_t n, char* binary) {
		int i = 0;
		for (int j = 31; j >= 0; j--) {
			binary[i++] = ((n >> j) & 1) + '0';
		}
		binary[32] = '\0';
	}

	void print() {
		logger->info("System:");
		char binary[33];
		uint32_to_binary(archetypeId, binary);
		logger->info("\tArchetypeId: %s",binary);
		logger->info("\tNum archetypes: %d", numArchetypes);
		for (int i = 0;i<numArchetypes;i++) {
			logger->info("\t\tArchetype: %p", archetypes[i]);
		}
	}

	void process() {
		for (int i = 0; i < numArchetypes; i++) {
			processArchetype(archetypes[i]);
		}
	}

private:
	virtual void processArchetype(Archetype* archetype) = 0;

protected:
	Logger* logger;

	ArchetypeId archetypeId;
	int numArchetypes;
	Archetype** archetypes;
};