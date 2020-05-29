#pragma once
#include "Component.h"
#include <string>

struct PlayerName : Component
{
	PlayerName() :
		Component(ecs::PlayerName),
		name_("")
	{}
	PlayerName(std::string n) :
		Component(ecs::PlayerName),
		name_(n)
	{}

	std::string name_;
};

