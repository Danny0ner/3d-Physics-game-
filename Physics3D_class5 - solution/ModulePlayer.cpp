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
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 0;
	car.wheels = new Wheel[0];
/*
	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width/20 + 0 * wheel_width, connection_height, half_length - wheel_radius * 2);
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
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
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
	car.wheels[1].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = false;
	car.wheels[1].drive = false;
	car.wheels[1].brake = true;
	car.wheels[1].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[2].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;
	*/
	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(0, 0, 10);


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
		vehicle->Push(50, 0, 0);
		NormalStr += 50;
		lastdirec = Forward;
	}
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_UP)
	{
		if (NormalStr >2000) vehicle->Push(-NormalStr / 2, 0, 0);
		else
		vehicle->Push(-NormalStr / 3, 0, 0);
		//else  if (NormalStr >300)  vehicle->Push(-NormalStr, 0, 0);
		//else vehicle->Push(-NormalStr / 15, 0, 0);
		NormalStr = 0;
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		vehicle->Push(-50, 0, 0);
		NormalBack += 50;
		lastdirec = Backward;
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_UP)
	{
		//if (NormalStr >1000)
		vehicle->Push(NormalBack / 3, 0, 0);
		//else  if (NormalStr >300)  vehicle->Push(-NormalStr, 0, 0);
		//else vehicle->Push(-NormalStr / 15, 0, 0);
		NormalBack = 0;
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
	{
		bodycito->applyTorque({ 1000,0,0 });
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		vehicle->Push(0, 0, 50);
		NormalRight += 50;
		lastdirec = Right;

	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_UP)
	{
		//if (NormalStr >1000)
		vehicle->Push(0, 0, -NormalRight / 3);
		//else  if (NormalStr >300)  vehicle->Push(-NormalStr, 0, 0);
		//else vehicle->Push(-NormalStr / 15, 0, 0);
		NormalRight = 0;
		bodycito->applyTorque({ -1000,0,0 });
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
	{
		bodycito->applyTorque({ -1000,0,0});
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		vehicle->Push(0, 0, -50);
		NormalLeft += 50;
		lastdirec = Left;
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_UP)
	{
		//if (NormalStr >1000)
		vehicle->Push(0, 0, NormalLeft / 3);
		//else  if (NormalStr >300)  vehicle->Push(-NormalStr, 0, 0);
		//else vehicle->Push(-NormalStr / 15, 0, 0);
		NormalLeft = 0;
		bodycito->applyTorque({ 1000,0,0 });
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		if (turn < TURN_DEGREES)
			turn += TURN_DEGREES;
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if (turn > -TURN_DEGREES)
			turn -= TURN_DEGREES;
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		brake = BRAKE_POWER;
	}
	switch (lastdirec) {
	case nothing: 
		break;
	case Forward:
		vehicle->Push(-5, 0, 0);
		break;
	case Backward:
		vehicle->Push(5, 0, 0);
		break;
	case Left:
		vehicle->Push(0, 0, 5);
		break;
	case Right:
		vehicle->Push(0, 0, -5);
		break;
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		bodycito->applyTorque({ 0,1000,0});
		LeftRotation += 1000;
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
	{
		bodycito->applyTorque({ 0,-LeftRotation,0 });
		LeftRotation = 0;
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		bodycito->applyTorque({ 0,-1000,0 });
		RightRotation += 1000;
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
	{
		bodycito->applyTorque({ 0,RightRotation,0 });
		RightRotation = 0;
	}

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);

	if (vehicle->GetKmh() == 0) lastdirec = nothing;
	vehicle->Render();

	char title[80];
	sprintf_s(title, "%.1f Km/h", vehicle->GetKmh());
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}


