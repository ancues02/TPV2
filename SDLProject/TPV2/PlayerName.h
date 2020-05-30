#pragma once
#include "Component.h"
#include <string.h>

// Componente para guardar los nombres de los cazas, por defecto es "Not Ready"
// Utilizamos la variable setted_ para comprobar
// si hemos puesto el nombre o no y evitar comprobar todos los caracteres
struct PlayerName : Component
{
	PlayerName() :
		Component(ecs::PlayerName){
		strcpy_s(&name_[0], 11, "Not Ready");
	}
	PlayerName(const char* n) :
		Component(ecs::PlayerName){
		strcpy_s(&name_[0], 11, n);
	}
	bool setted_ = false;
	char name_[11];
};

