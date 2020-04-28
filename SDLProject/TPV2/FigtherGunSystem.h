#pragma once
#include "System.h"
#include "InputHandler.h"
#include "Manager.h"
#include "SDLGame.h"

#include "Transform.h"
#include "BulletsSystem.h"
class FigtherGunSystem : public System
{
private:
	Uint32 cd = 0;	//registra la ultima vez que se disparó
	size_t limitTime = 250;//tiempo entre cada dissparo minimo
	
public:
	FigtherGunSystem() :
		System(ecs::_sys_FighterGun)
		{}

	
	void update() override;
};

