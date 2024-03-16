#include "GeometryLoaderSystem.h"

#include "RendererBase.h"

#include <vector>

GeometryLoaderSystem::GeometryLoaderSystem(){
	logger = new Logger("SYS_GEO");

	geometryLoader = new GeometryLoader();
	geometryLoader->registerGeometry(RECTANGLE, new Rectangle2D());
	geometryLoader->registerGeometry(TRIANGLE, new Triangle2D());
	geometryLoader->registerGeometry(CIRCLE, new Circle2D());
	geometryLoader->registerGeometry(CIRCLE_RING, new CircleRing2D());

	geometryLoader->registerGeometry(PLANE, new Plane3D());
	geometryLoader->registerGeometry(CUBE, new Cube3D());
	geometryLoader->registerGeometry(CONE, new Cone3D());
	geometryLoader->registerGeometry(CYLINDER, new Cylinder3D());
	geometryLoader->registerGeometry(HOLLOW_CYLINDER, new HollowCylinder3D());
	geometryLoader->registerGeometry(SPHERE, new Sphere3D());
}

GeometryLoaderSystem::~GeometryLoaderSystem(){
	geometryLoader->unregisterGeometry(RECTANGLE);
	geometryLoader->unregisterGeometry(TRIANGLE);
	geometryLoader->unregisterGeometry(CIRCLE);
	geometryLoader->unregisterGeometry(CIRCLE_RING);

	geometryLoader->unregisterGeometry(PLANE);
	geometryLoader->unregisterGeometry(CUBE);
	geometryLoader->unregisterGeometry(CONE);
	geometryLoader->unregisterGeometry(CYLINDER);
	geometryLoader->unregisterGeometry(HOLLOW_CYLINDER);
	geometryLoader->unregisterGeometry(SPHERE);
	delete geometryLoader;

	delete logger;
}

void GeometryLoaderSystem::processArchetype(Archetype* archetype){
	ComponentVector<GeometrySettings>* vecGeometrySettings= archetype->getComponentVector<GeometrySettings>();
	ComponentVector<MeshSettings>* vecMeshSettings = archetype->getComponentVector<MeshSettings>();
	GeometrySettings* geometrySettings;
	MeshSettings* meshSettings;
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	for (int i = 0;i<archetype->getNumEntities();i++) {
		geometrySettings = vecGeometrySettings->getComponentAtIndex(i);
		meshSettings = vecMeshSettings->getComponentAtIndex(i);

		geometryLoader->loadGeometry(*geometrySettings, meshSettings->hasTextureCoordinates, meshSettings->hasNormals, vertices, indices);
		meshSettings->meshId = renderer_loadMesh(*meshSettings, vertices.size(), vertices.data(), indices.size(), indices.data());

		vertices.clear();
		indices.clear();
	}
}