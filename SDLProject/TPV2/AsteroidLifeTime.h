#pragma once
#include "Component.h"
struct AsteroidLifeTime : public Component
{
	AsteroidLifeTime() :
		Component(ecs::AsteroidLifeTime), //
		gen_(0) //
	{
	}

	int gen_;
};

