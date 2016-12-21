#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

public:
	Cube s,floor, door6_1, door6_2, door6_3, door6_4, sensor1;
	Cylinder start, door1l, door1r , door2palo, door2circle, door4_1, door4_2, door4_3 , door7_1, door7_2, door7_3;
	
	PhysBody3D* map[20];
	PhysBody3D* sensoraro1;
	PhysBody3D* sensor;
};
