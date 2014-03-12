#include "pch.h"
#include "MainState.h"
#include "Tungsten\ServiceLocator.h"
#include "Tungsten\States\SpriteString.h"

using namespace Tungsten;

MainState::MainState()
:state(L"Assets\\Shaders\\PSWater.cso", L"Assets\\Shaders\\VSWater.cso")
{
	state.InitGrid(100,100,4);
	state.camera->SetPosition(50.0f, 3.0f, 50.0f);

	WaterPhysics::Wave wav;
	wav.direction = { 1.0f, 1.0f };
	wav.amplitude = 0.1f;
	wav.freq = 10.0f;
	wav.phase = 10.0f;
	state.SetWave(wav,0);

	wav.direction = { -1.0f, 4.0f };
	wav.amplitude = 0.3f;
	wav.freq = 0.1f;
	wav.phase = 5.0f;
	state.SetWave(wav, 1);
}

void MainState::Draw()
{
	Services.Graphics()->Refresh();
	

	state.Apply();
	state.Draw();
	Services.Graphics()->Present();
}

void MainState::Update(float deltaTime)
{
	InputService* input = Services.Input();
	Vector<2, long> move = input->mouse.GetMouseMovement();
	Vector<2> resolution = Services.Graphics()->GetResolution();
	Vector<2> relativeRotation = { move.x / resolution.x, move.y / resolution.y };
	float speed = 1.0f;
	relativeRotation.x *= speed;
	relativeRotation.y *= speed;
	state.camera->SetPerspectiveDelta(relativeRotation.x, relativeRotation.y);
	float moveSpeed = 1.0f;
	Vector<3> relativeMovement = { 0.0f, 0.0f, 0.0f };
	if (input->keyboard.IsPressed('w'))
		relativeMovement.z = 1.0f;
	if (input->keyboard.IsPressed('S'))
		relativeMovement.z = -1.0f;
	relativeMovement.z *= moveSpeed*deltaTime;

	state.camera->MoveRelative(relativeMovement.x,relativeMovement.y,relativeMovement.z);
}


MainState::~MainState()
{
}
