#include "ComponentVector.h"
#include "Hashmap.h"
#include "Archetype.h"

#include "ECS.h"

#include "Logger.h"

class Transform {
public:
	Transform() {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		scaleX = 1.0f;
		scaleY = 1.0f;
		scaleZ = 1.0f;
		angleX = 0.0f;
		angleY = 0.0f;
		angleZ = 0.0f;
	}

	Transform(float m_x,float m_y,float m_z,float m_scaleX,float m_scaleY,float m_scaleZ,float m_angleX,float m_angleY,float m_angleZ) {
		x = m_x;
		y = m_y;
		z = m_z;
		scaleX = m_scaleX;
		scaleY = m_scaleY;
		scaleZ = m_scaleZ;
		angleX = m_angleX;
		angleY = m_angleY;
		angleZ = m_angleZ;
	}
private:
	float x, y, z;
	float scaleX, scaleY, scaleZ;
	float angleX, angleY, angleZ;
};

class Mesh {
public:
	int mesh;
};

class Texture {
public:
	int texture;
};

class Color3f {
public:
	Color3f() {
		r = 0.0f;
		g = 0.0f;
		b = 0.0f;
	}

	Color3f(float m_r,float m_g,float m_b){
		r = m_r;
		g = m_g;
		b = m_b;
	}
private:
	float r, g, b;
};

class RenderColor2D {

};

class RenderColor3D {

};

class RenderTexture2D {

};

class RenderTexture3D {

};

class RenderGeometry2D {

};

class RenderGeometry3D {

};

enum GeometryType {
	RECTANGLE,
	CIRCLE,
	CIRCLE_RING,
	TRIANGLE,

	PLANE,
	CUBE,
	CYLINDER,
	HOLLOW_CYLINDER,
	CONE,
	SPHERE
};

class GeometrySettings {
public:
	GeometrySettings() {
		type = RECTANGLE;
		numPoints = 0;
		angle = 0.0f;
		innerRadius = 0.0f;
		numRings = 0;
	}

	GeometrySettings(GeometryType m_type,int m_numPoints,float m_angle,float m_innerRadius,int m_numRings) {
		type = m_type;
		numPoints = m_numPoints;
		angle = m_angle;
		innerRadius = m_innerRadius;
		numRings = m_numRings;
	}
private:
	GeometryType type;
	int numPoints;
	float angle;
	float innerRadius;
	int numRings;
};

class MeshSettings {
public:
	MeshSettings(){
		meshId = -1;
		is2D = false;
		hasColor = false;
		hasTextureCoordinates = false;
		hasNormals = false;
	}

	MeshSettings(int m_meshId,bool m_is2D,bool m_hasColor,bool m_hasTextureCoordinates,bool m_hasNormals) {
		meshId = m_meshId;
		is2D = m_is2D;
		hasColor = m_hasColor;
		hasTextureCoordinates = m_hasTextureCoordinates;
		hasNormals = m_hasNormals;
	}
private:
	int meshId;
	bool is2D;
	bool hasColor;
	bool hasTextureCoordinates;
	bool hasNormals;
};

class RenderNormal {
public:
	RenderNormal(int number) {
		m_number = number;
	}

	RenderNormal() {
	}

	~RenderNormal() {
	}

	int m_number=0;
};

struct MyHashCompute {
	uint32_t operator()(const std::string& string) const{
		//SDBM
		uint32_t hash = 0;
		const char* str = string.c_str();
		char c;
		while ((c = *str++)) {
			hash = c + (hash << 6) + (hash << 16) - hash;
		}

		//Mix it
		hash ^= hash >> 16;
		hash *= 0x3243f6a9U;
		hash ^= hash >> 16;

		return hash;
	}
};

class TestSystem {

};

void uint32_to_binary(uint32_t n, char* binary) {
	int i = 0;
	for (int j = 31; j >= 0; j--) {
		binary[i++] = ((n >> j) & 1) + '0';
	}
	binary[32] = '\0';
}

void testECS() {
	ECS* ecs = new ECS();
	Logger* logMain = new Logger("MAIN");

	//Register components
	ecs->registerComponent<GeometrySettings>(0);
	ecs->registerComponent<MeshSettings>(1);
	ecs->registerComponent<Color3f>(2);
	ecs->registerComponent<Transform>(3);

	//Generate Archetype id
	ArchetypeId id = ECS::IdGenerator<GeometrySettings, MeshSettings, Color3f, Transform>::getArchetypeId();
	char binary[33];
	uint32_to_binary(id, binary);
	logMain->info("ArchetypeId: %s", binary);

	//Find archetype
	Archetype* archetype = ecs->getOrCreateArchetype(id);

	//Create entity and add components
	EntityId planeColored = ecs->createEntity();
	archetype->addComponent<GeometrySettings>(planeColored, GeometrySettings(RECTANGLE, 0, 0.0f, 0.0f, 0));
	archetype->addComponent<MeshSettings>(planeColored, MeshSettings(5, true, false, true, false));
	archetype->addComponent<Color3f>(planeColored, Color3f(0.0f, 1.0f, 0.0f));
	archetype->addComponent<Transform>(planeColored, Transform(10.0f, 10.0f, 0.0f, 100.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.0f));

	//Destroy entity
	archetype->onEntityDestroyed(planeColored);
	ecs->destroyEntity(planeColored);

	//Unregister components
	ecs->unregisterComponent<GeometrySettings>();
	ecs->unregisterComponent<MeshSettings>();
	ecs->unregisterComponent<Color3f>();
	ecs->unregisterComponent<Transform>();







	ecs->addComponent(planeColored, Color3f(1.0f, 0.0f, 0.0f));
	ecs->removeComponent<Transform>(planeColored);

	ecs->registerSystem(TestSystem());
	ecs->systemAddComponents<TestSystem, Transform>();
	ecs->systemAddComponents<TestSystem, Transform, Color3f, MeshSettings>();

	delete ecs;
	delete logMain;
}

void testHashmap() {
	Logger* logMain = new Logger("MAIN");
	HashMap<std::string, int, MyHashCompute>* map = new HashMap<std::string, int, MyHashCompute>(50);
	/**map->put("Haus", 5);
	map->put("Baum", 15);
	map->put("Dach", 7);
	map->put("Elefant", 8);
	map->put("Kopf", 37);
	map->put("Gurke", 2);
	map->put("Tisch", 5);
	map->put("Lampe", 15);
	map->put("Stift", 7);
	map->put("Lautsprecher", 8);
	map->put("Knopf", 37);
	map->put("Atlas", 2);

	map->put("Haus1", 5);
	map->put("Baum1", 15);
	map->put("Dach1", 7);
	map->put("Elefant1", 8);
	map->put("Kopf1", 37);
	map->put("Gurke1", 2);
	map->put("Tisch1", 5);
	map->put("Lampe1", 15);
	map->put("Stift1", 7);
	map->put("Lautsprecher1", 8);
	map->put("Knopf1", 37);
	map->put("Atlas1", 2);

	map->put("Hausmeister", 5);
	map->put("Baumhaus", 15);
	map->put("Dachgiebel", 7);
	map->put("Elefantenstall", 8);
	map->put("Kopfgeld", 37);
	map->put("Gurkenglas", 2);
	map->put("Tischbein", 5);
	map->put("Lampenfieber", 15);
	map->put("anstiften", 7);
	map->put("Lautsprechergehäuse", 8);
	map->put("Knopfdruck", 37);
	map->put("Atlanten", 2);*/

	map->put("Handy", 5);//14
	map->put("Glas", 15);//26
	map->put("Kugel", 7);//13
	map->put("Kulli", 8);//17
	map->put("Qualle", 37);//38
	map->put("Bürostuhl", 2);//2
	map->put("Laptop", 5);//41
	map->put("Boden", 15);//31
	map->put("Buch", 7);//23
	map->put("Bildschirm", 8);//17
	map->put("Deckel", 37);//34
	map->put("Müllsack", 2);//4

	map->print();

	auto iterator = map->getIterator();
	iterator->reset();

	while (iterator->advance()!=nullptr) {
		auto node = iterator->get();
		logMain->info("Node is: %s",node->getKey().c_str());
	}

	delete map;
	delete logMain;
}

void testComponentVector() {
	ComponentVector<RenderNormal>* vec = new ComponentVector<RenderNormal>(4);
	vec->addComponent(1, RenderNormal(1));
	vec->addComponent(2, RenderNormal(2));
	vec->addComponent(3, RenderNormal(3));
	vec->removeComponent(1);
	vec->addComponent(4, RenderNormal(4));
	delete vec;
}

void testArchetype() {
	Archetype* archetype = new Archetype(5);
	archetype->addComponent(2, RenderNormal());
	archetype->addComponent(17, RenderNormal());
	archetype->removeComponent<RenderNormal>(2);
	delete archetype;
}

int main() {
	testECS();

	return 0;
}