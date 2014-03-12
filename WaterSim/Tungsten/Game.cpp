#include "pch.h"
#include "Game.h"


Game::Game()
{
	GameState::parent = this;
	frameTimer.Start();
}

Game::~Game()
{
	
}

void Game::Pop()
{
	gameStack.pop();
}

void Game::Push(GameState* p)
{
	gameStack.push(p);
}

void Game::RunFrame(int msPerFrame)
{
	frameTimer.Tick();
	if (!gameStack.empty())
	{
		gameStack.top()->Draw();
		do
		{
			gameStack.top()->Update(frameTimer.GetDynamicDelta());
			
		} while (msPerFrame / 1000.0f > frameTimer.GetDynamicDelta());
	}

}