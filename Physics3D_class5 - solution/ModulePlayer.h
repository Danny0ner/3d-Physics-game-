#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;
struct PhysVehicle3D;
enum lastdir {
	nothing,
	Forward,
	Backward,
	Left,
	Right,
};
#define MAX_ACCELERATION 0.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 1000.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:
	int Normal = 0;
	int NormalStr = 0;
	int NormalLeft = 0;
	int NormalRight = 0;
	int NormalBack = 0;

	btScalar LeftRotation = 0;
	btScalar RightRotation = 0;
	float matrix[12];
	lastdir lastdirec = nothing;
	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;

	Cylinder c1;
	Cylinder c2;
	Cylinder c3;
	Cylinder c4;

	PhysBody3D* cc1;
	PhysBody3D* cc2;
	PhysBody3D* cc3;
	PhysBody3D* cc4;
};