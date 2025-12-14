#include "SystemManager.h"

#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <iostream> 

namespace Fierce {
	SystemManager::SystemManager(){

	}

	SystemManager::~SystemManager(){
		for (auto* rule : m_rules_init) delete rule;
        for (auto* rule : m_rules_update) delete rule;
        for (auto* rule : m_rules_cleanUp) delete rule;
	}

	void SystemManager::addSystem(System* system){
		m_systems.push_back(system);
	}

	void SystemManager::removeSystem(System* system){
		auto it = std::remove(m_systems.begin(), m_systems.end(), system);
		m_systems.erase(it, m_systems.end());
	}

	void SystemManager::addRule(System* system1, SYSTEM_RULE_TYPE ruleType, System* system2){
        switch (ruleType) {
        case SYSTEM_RULE_TYPE::INIT_FIRST:
        case SYSTEM_RULE_TYPE::INIT_BEFORE:
        case SYSTEM_RULE_TYPE::INIT_AFTER:
        case SYSTEM_RULE_TYPE::INIT_LAST:
            m_rules_init.push_back(new SystemRule(system1, ruleType, system2));
            break;
        case SYSTEM_RULE_TYPE::UPDATE_FIRST:
        case SYSTEM_RULE_TYPE::UPDATE_BEFORE:
        case SYSTEM_RULE_TYPE::UPDATE_AFTER:
        case SYSTEM_RULE_TYPE::UPDATE_LAST:
            m_rules_update.push_back(new SystemRule(system1, ruleType, system2));
            break;
        case SYSTEM_RULE_TYPE::CLEANUP_FIRST:
        case SYSTEM_RULE_TYPE::CLEANUP_BEFORE:
        case SYSTEM_RULE_TYPE::CLEANUP_AFTER:
        case SYSTEM_RULE_TYPE::CLEANUP_LAST:
            m_rules_cleanUp.push_back(new SystemRule(system1, ruleType, system2));
            break;
        }
	}

	void SystemManager::initAllSystems(){
		for (System* system:m_systems_init) {
			system->initSystem("");
		}
	}

	void SystemManager::linkAllSystems(){
		for (System* system : m_systems) {
			system->linkSystem(nullptr);
		}
	}

	void SystemManager::updateAllSystems(){
		for (System* system : m_systems_update) {
			system->updateSystem();
		}
	}

	void SystemManager::cleanUpAllSystems(){
		for (System* system : m_systems_cleanUp) {
			system->cleanUpSystem();
		}
	}

    void SystemManager::sortAllSystems(){
        m_systems_init = sortSystems(m_rules_init);
        m_systems_update = sortSystems(m_rules_update);
        m_systems_cleanUp = sortSystems(m_rules_cleanUp);
    }

	std::vector<System*> SystemManager::sortSystems(std::vector<SystemRule*> rules){
        // Step 1: Build adjacency list (graph)
        std::unordered_map<System*, std::vector<System*>> graph;
        std::unordered_map<System*, int> indegree;

        // Initialize indegree
        for (System* system : m_systems)
            indegree[system] = 0;

        // Step 2: Convert rules to graph edges
        for (auto rule : rules){
            System* system1 = rule->m_system1;
            System* system2 = rule->m_system2;

            switch (rule->m_ruleType){
            case SYSTEM_RULE_TYPE::INIT_BEFORE:
            case SYSTEM_RULE_TYPE::UPDATE_BEFORE:
            case SYSTEM_RULE_TYPE::CLEANUP_BEFORE:
                graph[system1].push_back(system2);
                indegree[system2]++;
                break;

            case SYSTEM_RULE_TYPE::INIT_AFTER:
            case SYSTEM_RULE_TYPE::UPDATE_AFTER:
            case SYSTEM_RULE_TYPE::CLEANUP_AFTER:
                graph[system2].push_back(system1);
                indegree[system1]++;
                break;

            case SYSTEM_RULE_TYPE::INIT_FIRST:
            case SYSTEM_RULE_TYPE::UPDATE_FIRST:
            case SYSTEM_RULE_TYPE::CLEANUP_FIRST:
                for (System* otherSystem : m_systems){
                    if (otherSystem == system1) continue;
                    graph[system1].push_back(otherSystem);
                    indegree[otherSystem]++;
                }
                break;

            case SYSTEM_RULE_TYPE::INIT_LAST:
            case SYSTEM_RULE_TYPE::UPDATE_LAST:
            case SYSTEM_RULE_TYPE::CLEANUP_LAST:
                for (System* otherSystem : m_systems){
                    if (otherSystem == system1) continue;
                    graph[otherSystem].push_back(system1);
                    indegree[system1]++;
                }
                break;
            }
        }

        // Step 3: Topological sort (Kahn's Algo)
        std::queue<System*> queue;

        for (auto& pair : indegree)
            if (pair.second == 0)
                queue.push(pair.first);

        std::vector<System*> sorted;

        while (!queue.empty()){
            System* currentSystem = queue.front();
            queue.pop();
            sorted.push_back(currentSystem);

            for (System* neighborSystem : graph[currentSystem]){
                indegree[neighborSystem]--;
                if (indegree[neighborSystem] == 0)
                    queue.push(neighborSystem);
            }
        }

        // Step 4: Check for cycles (invalid rules)
        if (sorted.size() != m_systems.size()){
            std::cout << "Detected cyclic dependency during sorting of systems!" << "\n";
        }

        return sorted;
	}
}//end namespace