#ifndef SCENE_KINEMATICS_H
#define SCENE_KINEMATICS_H

#include "Scene.h"
#include "Mtx44.h"
#include "Camera.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "GameObject.h"
#include "Random.h"
#include "CollisionSystem.h"
#include <vector>

class SceneKinematics : public Scene
{
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHTENABLED,
		U_NUMLIGHTS,
		U_LIGHT0_TYPE,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_TEXT,
		GEO_BALL,
		GEO_MOTHERBASE,
		GEO_CUBE,
		GEO_WALL,
		GEO_ARROW,
		GEO_ARCHER,
		GEO_UNRECRUITED_ARCHER,
		GEO_WORKER,
		GEO_RABBIT,
		GEO_DEAD_RABBIT,
		GEO_MONSTER,
		GEO_LEADER,
		GEO_HEALER,
		GEO_TREASURE,
		NUM_GEOMETRY,
	};
public:
	SceneKinematics();
	~SceneKinematics();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderGO(GameObject *go);

private:
	void RandomiseTreasureLocation ( )
	{
		treasure.front ( ) = Vector3 { rng.RandFloat ( 0, m_worldWidth ), rng.RandFloat ( 0, m_worldHeight ), 0 };

		monsters.Clear ( );

		for ( std::size_t index = 0; index < 3; ++index )
		{
			monsters.Create ( Vector3 { rng.RandFloat ( 0, m_worldWidth ), rng.RandFloat ( 0, m_worldHeight ), 0 } );
		}
	}

	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	Camera camera;

	MS modelStack;
	MS viewStack;
	MS projectionStack;

	Light lights[1];

	bool bLightEnabled;

	float fps;

	//Physics
	std::vector<GameObject *> m_goList;
	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
	Vector3 m_gravity;
	GameObject *m_ghost;
	GameObject *m_timeGO;
	float m_timeEstimated1;
	float m_timeTaken1;
	float m_timeEstimated2;
	float m_timeTaken2;
	float m_heightEstimated;
	float m_heightMax;
	const float DAY_TIME_START = 0.f;
	const float NIGHT_TIME_START = 50.f;
	const float NIGHT_TIME_END = 100.f;

	//AI
	RNG rng;

	CountdownSystem timer_system;
	PhysicsSystem physics_system;
	CollisionSystem collision_system;
	PathFinder path_finding_system;

	std::vector<Vector3> treasure;
	Leaders leaders;
	Archers archers;
	Healers healers;
	Arrows arrows;
	Monsters monsters;
	Tanks tanks;

};

#endif