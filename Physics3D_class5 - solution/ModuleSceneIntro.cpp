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
	start.radius = 7;
	start.height = 1;
	start.SetRotation(120, (0, 0, 2));
	start.SetPos(0, 1, 0);
	start.color = Green;
	map[0] = App->physics->AddBody(start, 0.0f);


	door1l.radius = 0.5f;
	door1l.height = 20;
	door1l.SetRotation(120, (0, 0, 1));
	door1l.SetPos(30, 10, -5);
	door1l.color = Red;
	map[1] = App->physics->AddBody(door1l, 0.0f);
	
	door1r.radius = 0.5f;
	door1r.height = 20;
	door1r.SetRotation(120, (0, 0, 1));
	door1r.SetPos(30, 10, 5);
	door1r.color = Red;
	map[2] = App->physics->AddBody(door1r, 0.0f);

	door2palo.radius = 0.5f;
	door2palo.height = 20;
	door2palo.SetRotation(120, (0, 0, 1));
	door2palo.SetPos(70, 10, 0);
	door2palo.color = White;
	map[3] = App->physics->AddBody(door2palo, 0.0f);

	door4_1.radius = 0.5f;
	door4_1.height = 8;
	door4_1.SetRotation(120, (0, 0, 1));
	door4_1.SetPos(0, 4, -30);
	door4_1.color = White;
	map[4] = App->physics->AddBody(door4_1, 0.0f);

	door4_2.radius = 0.5f;
	door4_2.height = 8;
	door4_2.SetRotation(120, (0, 0, 1));
	door4_2.SetPos(8, 4, -30);
	door4_2.color = White;
	map[5] = App->physics->AddBody(door4_2, 0.0f);

	door4_3.radius = 0.5f;
	door4_3.height = 8;
	door4_3.SetPos(4, 7, -30);
	door4_3.color = White;
	map[6] = App->physics->AddBody(door4_3, 0.0f);

	door7_1.radius = 0.5f;
	door7_1.height = 8;
	door7_1.SetRotation(120, (0, 0, 1));
	door7_1.SetPos(70, 4, -30);
	door7_1.color = White;
	map[7] = App->physics->AddBody(door7_1, 0.0f);

	door7_2.radius = 0.5f;
	door7_2.height = 8;
	door7_2.SetRotation(120, (0, 0, 1));
	door7_2.SetPos(78, 4, -30);
	door7_2.color = White;
	map[8] = App->physics->AddBody(door7_2, 0.0f);

	door7_3.radius = 0.5f;
	door7_3.height = 8;
	door7_3.SetPos(74, 7, -30);
	door7_3.color = White;
	map[9] = App->physics->AddBody(door7_3, 0.0f);

	s.size = vec3(5, 3, 1);
	s.SetPos(0, 2.5f, 20);

	door6_1.size = vec3(12, 7, 1);
	door6_1.SetPos(50, 4, -20);
	map[10] = App->physics->AddBody(door6_1, 0.0f);

	door6_2.size = vec3(2, 10, 1);
	door6_2.SetPos(55, 9, -20);
	map[11] = App->physics->AddBody(door6_2, 0.0f);

	door6_3.size = vec3(2, 10, 1);
	door6_3.SetPos(45, 9, -20);
	map[12] = App->physics->AddBody(door6_3, 0.0f);

	door6_4.size = vec3(10, 2, 1);
	door6_4.SetPos(50, 13, -20);
	map[13] = App->physics->AddBody(door6_4, 0.0f);

	Flooor.size = vec3(120, 0, 100);
	Flooor.SetPos(50, 0.1f, -40);
	map[14] = App->physics->AddBody(Flooor, 0.0f);
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
	
	s.Render();
	Flooor.Render();
	door6_1.Render();
	door6_2.Render();
	door6_3.Render();
	door6_4.Render();
	start.Render();
	door1l.Render();
	door1r.Render();
	door2palo.Render();
	door4_1.Render();
	door4_2.Render();
	door4_3.Render();
	door7_1.Render();
	door7_2.Render();
	door7_3.Render();
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body1 == sensoraro1) {
		LOG("Hit Aro!");
	}
	else LOG("Hit!");
}

