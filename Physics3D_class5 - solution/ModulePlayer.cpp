#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");


	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis_size.Set(4, 1, 4);
	car.chassis_offset.Set(0, 1, 0);
	car.mass = 200.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.6f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x* 0.5f;
	float half_length = car.chassis_size.z*0.5f;

	vec3 direction(0, 1, 0);
	vec3 axis(-1, 0, 0);





	car.num_wheels = 0;
	car.wheels = new Wheel[0];

	/*
	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width + 1, connection_height , half_length*2);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(half_width-4, connection_height + 1, half_length +3);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width + 1, connection_height + 2, half_length -3);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(half_width-4, connection_height + 1, half_length * 2);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	*/
	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(0, 2, 0);

	/////////////////////////// helices//////////////////
	c1.height = 0.01f;
	c1.radius = 1;
	c2.height = 0.01f;
	c2.radius = 1;
	c3.height = 0.01f;
	c3.radius = 1;
	c4.height = 0.01f;
	c4.radius = 1;
	c1.color = Red;

	btVector3 helix(0, -1, 0);
	btVector3 helix2(0, 2, 0);
	btVector3 helix3(0, 1, 0);
	//cc1 = App->physics->AddBody(c1, 0.1f);
	//App->physics->Add_Hinge_Constraint(*vehicle->GetRigidBody(), *cc1->GetRigidBody(), helix2, helix, helix3, helix3, false);
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	btRigidBody* bodycito;
	bodycito = vehicle->vehicle->getRigidBody();
	turn = acceleration = brake = 0.0f;
	mat4x4 trans;
	this->vehicle->GetTransform(&trans);
	vec3 PushVectorFront;
	vec3 PushVectorLeft;
	vec3 PushVectorRight;
	vec3 PushVectorBack;
	vec3 AirFriction;
	vec3 AirFric;
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		acceleration = MAX_ACCELERATION;
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
	{
		vehicle->Push(0, 70, 0);
		Normal += 70;
	}
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		if (Normal > 1000)
			vehicle->Push(0, -Normal / 7, 0);
		else  if (Normal > 300)  vehicle->Push(0, -Normal / 10, 0);
		else vehicle->Push(0, -Normal / 15, 0);
		Normal = 0;

	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{

		vec3 WorldPush(50, 0, 0);
		PushVectorFront.x = trans[0] * WorldPush.x + trans[1] * WorldPush.y + trans[2] * WorldPush.z;
		PushVectorFront.y = trans[4] * WorldPush.x + trans[5] * WorldPush.y + trans[6] * WorldPush.z;
		PushVectorFront.z = trans[8] * WorldPush.x + trans[9] * WorldPush.y + trans[10] * WorldPush.z;
		vehicle->Push(PushVectorFront.x, PushVectorFront.y, -PushVectorFront.z);
		//vehicle->Push(50, 0, 0);
		NormalStr += 50;
		lastdirec = Forward;
	}
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_UP)
	{
		if (NormalStr >2000) vehicle->Push(-PushVectorFront.x, -PushVectorFront.y, PushVectorFront.z);
		else
			vehicle->Push(-PushVectorFront.x, -PushVectorFront.y, PushVectorFront.z);
		//else  if (NormalStr >300)  vehicle->Push(-NormalStr, 0, 0);
		//else vehicle->Push(-NormalStr / 15, 0, 0);
		NormalStr = 0;
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		vec3 WorldPush(-50, 0, 0);
		PushVectorBack.x = trans[0] * WorldPush.x + trans[1] * WorldPush.y + trans[2] * WorldPush.z;
		PushVectorBack.y = trans[4] * WorldPush.x + trans[5] * WorldPush.y + trans[6] * WorldPush.z;
		PushVectorBack.z = trans[8] * WorldPush.x + trans[9] * WorldPush.y + trans[10] * WorldPush.z;
		vehicle->Push(PushVectorBack.x, PushVectorBack.y, -PushVectorBack.z);
		//vehicle->Push(-50, 0, 0);
		NormalBack += 50;
		lastdirec = Backward;
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_UP)
	{
		//if (NormalStr >1000)
		vehicle->Push(-PushVectorBack.x, -PushVectorBack.y, PushVectorBack.z);
		//else  if (NormalStr >300)  vehicle->Push(-NormalStr, 0, 0);
		//else vehicle->Push(-NormalStr / 15, 0, 0);
		NormalBack = 0;
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
	{
		//bodycito->applyTorque({ 1000,0,0 });
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		vec3 WorldPush(0, 0, 50);
		PushVectorLeft.x = trans[0] * WorldPush.x + trans[1] * WorldPush.y + trans[2] * WorldPush.z;
		PushVectorLeft.y = trans[4] * WorldPush.x + trans[5] * WorldPush.y + trans[6] * WorldPush.z;
		PushVectorLeft.z = trans[8] * WorldPush.x + trans[9] * WorldPush.y + trans[10] * WorldPush.z;
		vehicle->Push(PushVectorLeft.x, PushVectorLeft.y, -PushVectorLeft.z);
		//AirFric = (PushVectorFront.x, PushVectorFront.y, -PushVectorFront.z);
		//vehicle->Push(0, 0, 50);
		NormalRight += 50;
		lastdirec = Left;

	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_UP)
	{
		//if (NormalStr >1000)
		vehicle->Push(-PushVectorLeft.x, -PushVectorLeft.y, PushVectorLeft.z);
		//else  if (NormalStr >300)  vehicle->Push(-NormalStr, 0, 0);
		//else vehicle->Push(-NormalStr / 15, 0, 0);
		NormalRight = 0;
		//bodycito->applyTorque({ -1000,0,0 });
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
	{
		//bodycito->applyTorque({ -1000,0,0});
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		vec3 WorldPush(0, 0, -50);
		PushVectorRight.x = trans[0] * WorldPush.x + trans[1] * WorldPush.y + trans[2] * WorldPush.z;
		PushVectorRight.y = trans[4] * WorldPush.x + trans[5] * WorldPush.y + trans[6] * WorldPush.z;
		PushVectorRight.z = trans[8] * WorldPush.x + trans[9] * WorldPush.y + trans[10] * WorldPush.z;
		vehicle->Push(PushVectorRight.x, PushVectorRight.y, -PushVectorRight.z);
		//AirFric = (PushVectorFront.x, PushVectorFront.y, -PushVectorFront.z);
		//vehicle->Push(0, 0, -50);

		lastdirec = Right;
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_UP)
	{
		vehicle->Push(-PushVectorRight.x, -PushVectorRight.y, PushVectorRight.z);
	}
	
	switch (lastdirec) {
	case nothing:
		break;
		
	case Forward:
		AirFric =( -13, 0, 0 );
		AirFriction.x = trans[0] * AirFric.x + trans[1] * AirFric.y + trans[2] * AirFric.z;
		AirFriction.y = trans[4] * AirFric.x + trans[5] * AirFric.y + trans[6] * AirFric.z;
		AirFriction.z = trans[8] * AirFric.x + trans[9] * AirFric.y + trans[10] * AirFric.z;
		vehicle->Push(AirFriction.x, AirFriction.y, -AirFriction.z);
		break;
	case Backward:
		AirFric = (13, 0, 0);
		AirFriction.x = trans[0] * AirFric.x + trans[1] * AirFric.y + trans[2] * AirFric.z;
		AirFriction.y = trans[4] * AirFric.x + trans[5] * AirFric.y + trans[6] * AirFric.z;
		AirFriction.z = trans[8] * AirFric.x + trans[9] * AirFric.y + trans[10] * AirFric.z;
		vehicle->Push(AirFriction.x, AirFriction.y, -AirFriction.z);
		
		break;
	case Left:
		//AirFric = (0, 0, -13);
		AirFriction.x = trans[0] * AirFric.x + trans[1] * AirFric.y + trans[2] * AirFric.z;
		AirFriction.y = trans[4] * AirFric.x + trans[5] * AirFric.y + trans[6] * AirFric.z;
		AirFriction.z = trans[8] * AirFric.x + trans[9] * AirFric.y + trans[10] * AirFric.z;
		vehicle->Push(-AirFriction.x, 0, -AirFriction.z);
		break;
	case Right:
	
		AirFriction.x = trans[0] * AirFric.x + trans[1] * AirFric.y + trans[2] * AirFric.z;
		AirFriction.y = trans[4] * AirFric.x + trans[5] * AirFric.y + trans[6] * AirFric.z;
		AirFriction.z = trans[8] * AirFric.x + trans[9] * AirFric.y + trans[10] * AirFric.z;
		vehicle->Push(AirFriction.x, 0, -AirFriction.z);
		break;
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		bodycito->applyTorque({ 0,1000,0 });
		LeftRotation += 1000;
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
	{
		bodycito->applyTorque({ 0,-LeftRotation,0 });
		LeftRotation = 0;
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		bodycito->applyTorque({ 0,-1000,0 });
		RightRotation += 1000;
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
	{
		bodycito->applyTorque({ 0,RightRotation,0 });
		RightRotation = 0;
	}
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		bodycito->applyTorque({0,0, 1000 });
		FrontRotation += 1000;
	}
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_UP)
	{
		bodycito->applyTorque({ 0,0,-FrontRotation});
		FrontRotation = 0;
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		bodycito->applyTorque({ 0,0, -1000 });
		BackRotation += 1000;
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
	{
		bodycito->applyTorque({ 0,0,BackRotation });
		BackRotation = 0;
	}
	if (vehicle->GetKmh() < 10 && vehicle->GetKmh() > -10) lastdirec = nothing;
	vehicle->Render();




	return UPDATE_CONTINUE;
}



