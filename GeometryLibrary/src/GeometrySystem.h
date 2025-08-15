#pragma once

#include "src/include/LoggingSystem.h"
#include "src/utils/System.h"

#include "GeometryLoader.h"

namespace Fierce {

	class GeometrySystem : public System{
	public:
		GeometrySystem();
		~GeometrySystem();

		void initSystem(std::string assetDirectory) override;
		void linkSystem(System* system) override;
		void updateSystem() override;
		void cleanUpSystem() override;


		void loadGeometry(GeometryType type, int numPoints, float angle, float innerRadius, int numRings, std::vector<float>& vertices, std::vector<uint16_t>& indices);

	private:
		LoggingSystem* m_loggingSystem = nullptr;
		Logger* m_logger = nullptr;

		GeometryLoader* m_loader = nullptr;
	};
}