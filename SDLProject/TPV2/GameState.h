#pragma once
#include "Component.h"
struct GameState : public Component
{
	enum State {
		Stop, Running, Win, Lose
	};
	GameState(State state) :
		Component(ecs::GameState) //		
	{
		currentState = state;
	}

	GameState() :
		Component(ecs::GameState)//
	{
		currentState = Stop;
	}

	State currentState;
};

