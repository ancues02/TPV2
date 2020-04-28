#pragma once

#include "Collisions.h"
#include "Manager.h"
#include "FighterSystem.h"
#include "Transform.h"
#include "BulletsSystem.h"
#include "AsteroidSystem.h"
#include "Score.h"
class CollisionSystem: public System {
public:
	CollisionSystem() :
		System(ecs::_sys_Collisions) {
	}

	void update()override;
};

