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

	door5palo.radius = 0.5f;
	door5palo.height = 10;
	door5palo.SetRotation(120, (0, 0, 1));
	door5palo.SetPos(40, 5, -40);
	door5palo.color = White;
	map[27] = App->physics->AddBody(door5palo, 0.0f);

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


	///////////////////RING 1 ///////////////

	vec3 Ringbox(1, 1, 2);
	
	////radius////
	ring1.size = Ringbox;
	ring2.size = Ringbox;
	ring3.size = Ringbox;
	ring4.size = Ringbox;
	ring5.size = Ringbox;
	ring6.size = Ringbox;
	ring7.size = Ringbox;
	ring8.size = Ringbox;
	ring9.size = Ringbox;
	ring10.size = Ringbox;
	ring11.size = Ringbox;
	ring12.size = Ringbox;


	
	////Position////


	ring1.SetPos(70, 20, 0);
	ring2.SetPos(70, 20.6f, -2);
	ring2.SetRotation(36, { 1,0,0 });
	ring3.SetPos(70, 22.4f, -3.4f);
	ring3.SetRotation(72, { 1,0,0 });
	ring4.SetPos(70, 24.5f, -3.8f);
	ring4.SetRotation(90, { 1,0,0 });
	ring5.SetPos(70, 26.6, -3.4f);
	ring5.SetRotation(116, { 1,0,0 });
	ring6.SetPos(70, 28.2f, -2);
	ring6.SetRotation(152, { 1,0,0 });
	ring7.SetPos(70, 28.7, -0);
	ring7.SetRotation(0, { 1,0,0 });
	ring8.SetPos(70, 28.2, 2);
	ring8.SetRotation(-152, { 1,0,0 });
	ring9.SetPos(70, 26.6, 3.4f);
	ring9.SetRotation(-116, { 1,0,0 });
	ring10.SetPos(70, 24.5f, 3.8f);
	ring10.SetRotation(90, { 1,0,0 });
	ring11.SetPos(70, 22.4f, 3.4f);
	ring11.SetRotation(-72, { 1,0,0 });
	ring12.SetPos(70, 20.6f, 2);
	ring12.SetRotation(-36, { 1,0,0 });

	//////ADD RING/////
	map[15] = App->physics->AddBody(ring1, 0.0f);
	map[16] = App->physics->AddBody(ring2, 0.0f);
	map[17] = App->physics->AddBody(ring3, 0.0f);
	map[18] = App->physics->AddBody(ring4, 0.0f);
	map[19] = App->physics->AddBody(ring5, 0.0f);
	map[20] = App->physics->AddBody(ring6, 0.0f);
	map[21] = App->physics->AddBody(ring7, 0.0f);
	map[22] = App->physics->AddBody(ring8, 0.0f);
	map[23] = App->physics->AddBody(ring9, 0.0f);
	map[24] = App->physics->AddBody(ring10, 0.0f);
	map[25] = App->physics->AddBody(ring11, 0.0f);
	map[26] = App->physics->AddBody(ring12, 0.0f);


	////////Ring 2////////
	ring13.size = Ringbox;
	ring14.size = Ringbox;
	ring15.size = Ringbox;
	ring16.size = Ringbox;
	ring17.size = Ringbox;
	ring18.size = Ringbox;
	ring19.size = Ringbox;
	ring20.size = Ringbox;
	ring21.size = Ringbox;
	ring22.size = Ringbox;
	ring23.size = Ringbox;
	ring24.size = Ringbox;



	////Position////

	//(70, 10, 0);
	//(40, 5, -40);

	ring13.SetPos(40, 10, -40);
	ring14.SetPos(40, 10.6f, -42);
	ring14.SetRotation(36, { 1,0,0 });
	ring15.SetPos(40, 12.4f, -43.4f);
	ring15.SetRotation(72, { 1,0,0 });
	ring16.SetPos(40, 14.5f, -43.8f);
	ring16.SetRotation(90, { 1,0,0 });
	ring17.SetPos(40, 16.6, -43.4f);
	ring17.SetRotation(116, { 1,0,0 });
	ring18.SetPos(40, 18.2f, -42);
	ring18.SetRotation(152, { 1,0,0 });
	ring19.SetPos(40, 18.7, -40);
	ring19.SetRotation(0, { 1,0,0 });
	ring20.SetPos(40, 18.2, -38);
	ring20.SetRotation(-152, { 1,0,0 });
	ring21.SetPos(40, 16.6, -36.4f);
	ring21.SetRotation(-116, { 1,0,0 });
	ring22.SetPos(40, 14.5f, -36.0f);
	ring22.SetRotation(90, { 1,0,0 });
	ring23.SetPos(40, 12.4f, -36.4f);
	ring23.SetRotation(-72, { 1,0,0 });
	ring24.SetPos(40, 10.6f, -38);
	ring24.SetRotation(-36, { 1,0,0 });

	//////ADD RING/////
	map[28] = App->physics->AddBody(ring13, 0.0f);
	map[29] = App->physics->AddBody(ring14, 0.0f);
	map[30] = App->physics->AddBody(ring15, 0.0f);
	map[31] = App->physics->AddBody(ring16, 0.0f);
	map[32] = App->physics->AddBody(ring17, 0.0f);
	map[33] = App->physics->AddBody(ring18, 0.0f);
	map[34] = App->physics->AddBody(ring19, 0.0f);
	map[35] = App->physics->AddBody(ring20, 0.0f);
	map[36] = App->physics->AddBody(ring21, 0.0f);
	map[37] = App->physics->AddBody(ring22, 0.0f);
	map[38] = App->physics->AddBody(ring23, 0.0f);
	map[39] = App->physics->AddBody(ring24, 0.0f);
	

	Flooor.size = vec3(120, 0, 100);
	Flooor.SetPos(50, 0.1f, -40);
	map[14] = App->physics->AddBody(Flooor, 0.0f);
	/////////////////////////SENSORS////////////////////////////
	sensor1.size = vec3(1,20,9);
	sensor1.SetPos(30, 10, 0);

	Door1 = App->physics->AddBody(sensor1, 0.0f);
	Door1->SetAsSensor(true);
	Door1->collision_listeners.add(this);
	sensor2.height = 1;
	sensor2.radius = 4;
	sensor2.SetPos(70, 24, 0);
	Door2 = App->physics->AddBody(sensor2, 0.0f);
	Door2->SetAsSensor(true);
	Door2->collision_listeners.add(this);


//	sensor->SetAsSensor(true);
	//sensor->collision_listeners.add(this);
	

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

	//sensor->GetTransform(&s.transform);
	//sensor1.Render();
	
	Flooor.Render();
	door6_1.Render();
	door6_2.Render();
	door6_3.Render();
	door6_4.Render();
	start.Render();
	door1l.Render();
	door1r.Render();
	door2palo.Render();
	door5palo.Render();
	door4_1.Render();
	door4_2.Render();
	door4_3.Render();
	door7_1.Render();
	door7_2.Render();
	door7_3.Render();


	/////////Ring Render/////////
	ring1.Render();
	ring2.Render();
	ring3.Render();
	ring4.Render();
	ring5.Render();
	ring6.Render();
	ring7.Render();
	ring8.Render();
	ring9.Render();
	ring10.Render();
	ring11.Render();
	ring12.Render();


	/////////Ring 2 Render /////////
	ring13.Render();
	ring14.Render();
	ring15.Render();
	ring16.Render();
	ring17.Render();
	ring18.Render();
	ring19.Render();
	ring20.Render();
	ring21.Render();
	ring22.Render();
	ring23.Render();
	ring24.Render();

	////////Ring Colour //////////

	




	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body1 == Door1 || body2 == Door1) {
		LOG("Hit Aro!");
		door2palo.color = Red;
		door1l.color = White;
		door1r.color = White;
		ring1.color.Set(255, 255, 0,1);
		ring2.color.Set(255, 255, 0, 1);
		ring3.color.Set(255, 255, 0, 1);
		ring4.color.Set(255, 255, 0, 1);
		ring5.color.Set(255, 255, 0, 1);
		ring6.color.Set(255, 255, 0, 1);
		ring7.color.Set(255, 255, 0, 1);
		ring8.color.Set(255, 255, 0, 1);
		ring9.color.Set(255, 255, 0, 1);
		ring10.color.Set(255, 255, 0, 1);
		ring11.color.Set(255, 255, 0, 1);
		ring12.color.Set(255, 255, 0, 1);
	}
	if (body1 == Door2 || body2 == Door2) {
		door2palo.color = White;
		ring1.color = White;
		ring2.color = White;
		ring3.color = White;
		ring4.color = White;
		ring5.color = White;
		ring6.color = White;
		ring7.color = White;
		ring8.color = White;
		ring9.color = White;
		ring10.color = White;
		ring11.color = White;
		ring12.color = White;
	}
	else LOG("Hit!");
}

