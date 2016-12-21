#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	s.size = vec3(5, 3, 1);
	s.SetPos(0, 2.5f, 20);
	s1.size = vec3(1, 2, 10);
	s1.SetPos(20, 5, 1);
	aro1[0] = App->physics->AddBody(s1, 0.0f);
	s2.size = vec3(1, 10, 2);
	s2.SetPos(20, 9, -3);
	aro1[1] = App->physics->AddBody(s2, 0.0f);
	s3.size = vec3(1, 10, 2);
	s3.SetPos(20, 9, 5);
	aro1[2] = App->physics->AddBody(s3, 0.0f);
	s4.size = vec3(1, 2, 10);
	s4.SetPos(20, 13, 1);
	aro1[3] = App->physics->AddBody(s4, 0.0f);
	sensor1.size = vec3(1,5,5);
	sensor1.SetPos(20, 13, 1);
	sensoraro1 = App->physics->AddBody(sensor1, 0.0f);
	sensoraro1->SetAsSensor(true);
	sensoraro1->collision_listeners.add(this);

	sensor = App->physics->AddBody(s, 0.0f);
	sensor->SetAsSensor(true);
	sensor->collision_listeners.add(this);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	sensor->GetTransform(&s.transform);
	sensoraro1->GetTransform(&sensor1.transform);
	sensor1.Render();
	s.Render();
	s1.Render();
	s2.Render();
	s3.Render();
	s4.Render();
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	LOG("Hit!");
}

