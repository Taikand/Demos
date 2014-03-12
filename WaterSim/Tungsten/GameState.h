#pragma once
#include "IGame.h"
class GameState
{
protected:
	static IGame* parent;
	friend class Game;
public:
	GameState();
	virtual void Draw() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual ~GameState() = 0;
};

