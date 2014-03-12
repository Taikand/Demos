#pragma once
#include "Tungsten\GameState.h"
#include "WaterPhysics.h"
#include "Tungsten\Camera.h"
class MainState : public GameState
{
private:
	Tungsten::WaterPhysics state;
	
public:
	
	void Draw();
	void Update(float deltaTime);
	MainState();
	~MainState();
};

