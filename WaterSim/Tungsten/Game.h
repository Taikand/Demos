#pragma once
#include <stack>
#include "Tungsten\Timer.h"
#include "GameState.h"
class Game:
	public IGame
{
private:
	std::stack<GameState*> gameStack;
	Timer frameTimer;
public:
	void Push(GameState*);
	void Pop();
	//The minimum amount of time a frame has to run.
	void RunFrame(int msPerFrame);
	Game();
	~Game();
};

