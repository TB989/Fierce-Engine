#pragma once

#include "src/systems/System.h"
#include "src/systems/IGeometrySystem.h"
#include "src/systems/ILoggingSystem.h"

#include "GeometryLoader.h"

namespace Fierce {

	class GeometrySystem : public IGeometrySystem{
	public:
		GeometrySystem();
		~GeometrySystem();

		void initSystem(std::string assetDirectory) override;
		void linkSystem(System* system) override;
		void updateSystem() override;
		void cleanUpSystem() override;

		std::string getName() override;

		void loadGeometry(GeometryType type, int numPoints, float angle, float innerRadius, int numRings, std::vector<float>& vertices, std::vector<uint16_t>& indices) override;

	private:
		ILoggingSystem* m_loggingSystem = nullptr;
		ILogger* m_logger = nullptr;

		GeometryLoader* m_loader = nullptr;
	};
}