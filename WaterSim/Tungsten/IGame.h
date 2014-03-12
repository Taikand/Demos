#pragma once
class GameState;
class IGame
{
public:
	
	virtual void Push(GameState*)=0;
	virtual void Pop()=0;
	virtual ~IGame() = 0{};
	virtual void RunFrame(int)=0;
};

