#pragma once
#include "Component.h"
struct Health : public Component
{
	Health(int init_Health) :
		Component(ecs::Health), //
		init_Health_(init_Health),
		health_(init_Health)
	{
	}

	Health() :
		Component(ecs::Health), //
		init_Health_(3),
		health_(3)
	{
	}

	int health_, init_Health_;
};

