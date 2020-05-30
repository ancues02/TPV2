#pragma once
#include "Component.h"
#include <iostream>

struct PlayerName : Component
{
	PlayerName() :
		Component(ecs::PlayerName){
		strcpy_s(&name_[0], 11, "Not Ready");
		//strcpy_s(name, 11, "Hola");
		//std::cout << name << " " << std::strlen(name) << std::endl;
		/*
		for (int i = 0; i < 11; i++) {
			std::cout << name_[i] << std::endl;
		}*/
	}
	PlayerName(const char* n) :
		Component(ecs::PlayerName){
		strcpy_s(&name_[0], 11, n);
	}
	bool setted_ = false;
	char name_[11];
	//char* name;
};

