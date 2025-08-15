#include "GeometrySystem.h"

namespace Fierce {

	Fierce::GeometrySystem::GeometrySystem(){
		m_loader = new GeometryLoader();
		m_loader->registerGeometry(GeometryType::RECTANGLE, new Rectangle2D());
		m_loader->registerGeometry(GeometryType::CIRCLE, new Circle2D());
		m_loader->registerGeometry(GeometryType::CIRCLE_RING, new CircleRing2D());
		m_loader->registerGeometry(GeometryType::TRIANGLE, new Triangle2D());

		m_loader->registerGeometry(GeometryType::PLANE, new Plane3D());
		m_loader->registerGeometry(GeometryType::CUBE, new Cube3D());
		m_loader->registerGeometry(GeometryType::CYLINDER, new Cylinder3D());
		m_loader->registerGeometry(GeometryType::HOLLOW_CYLINDER, new HollowCylinder3D());
		m_loader->registerGeometry(GeometryType::CONE, new Cone3D());
		m_loader->registerGeometry(GeometryType::SPHERE, new Sphere3D());
	}

	GeometrySystem::~GeometrySystem(){
		m_loader->unregisterGeometry(GeometryType::RECTANGLE);
		m_loader->unregisterGeometry(GeometryType::CIRCLE);
		m_loader->unregisterGeometry(GeometryType::CIRCLE_RING);
		m_loader->unregisterGeometry(GeometryType::TRIANGLE);

		m_loader->unregisterGeometry(GeometryType::PLANE);
		m_loader->unregisterGeometry(GeometryType::CUBE);
		m_loader->unregisterGeometry(GeometryType::CYLINDER);
		m_loader->unregisterGeometry(GeometryType::HOLLOW_CYLINDER);
		m_loader->unregisterGeometry(GeometryType::CONE);
		m_loader->unregisterGeometry(GeometryType::SPHERE);
		delete m_loader;
	}

	void GeometrySystem::initSystem(std::string assetDirectory){
		if (m_loggingSystem != nullptr) {
			m_logger = m_loggingSystem->createLogger("GEO", true, "ALL_LOGS");
			m_logger->info("Init geometry system");
		}
	}

	void GeometrySystem::linkSystem(System* system){
		if (dynamic_cast<LoggingSystem*>(system)) {
			m_loggingSystem = (LoggingSystem*)system;
		}
	}

	void GeometrySystem::updateSystem(){

	}

	void GeometrySystem::cleanUpSystem(){
		if (m_logger != nullptr) {
			m_logger->info("Clean up geometry system");
			m_loggingSystem->deleteLogger(m_logger);
		}
	}

	void GeometrySystem::loadGeometry(GeometryType type, int numPoints, float angle, float innerRadius, int numRings, std::vector<float>& vertices, std::vector<uint16_t>& indices) {
		m_loader->loadGeometry(type,numPoints,angle,innerRadius,numRings,vertices,indices);
	}
}