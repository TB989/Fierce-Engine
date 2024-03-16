#include "ECS.h"

HashMap<const char*, ComponentId>* ECS::m_componentRegistry = new HashMap<const char*, ComponentId>(32);