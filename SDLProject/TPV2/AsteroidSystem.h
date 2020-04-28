#pragma once
#include "System.h"
#include <cmath>
#include "SDL_macros.h"
#include "AsteroidPool.h"
#include "Manager.h"
#include "SDLGame.h"

class AsteroidSystem : public System
{
private:
	std::size_t numOfAsteroids_ = 0;
public:
	AsteroidSystem() :
		System(ecs::_sys_Asteroids) {
	}

	// - desactivar el asteroide “a” y crear 2 asteroides como en la práctica 1.
	void onCollisionWithBullet(Entity* a, Entity* b);


	void addAsteroids(int n);


	void update() override;

	void disableAll() {
		for (auto& e : mngr_->getGroupEntities(ecs::_grp_Asteroid)) {
			e->setActive(false);
		}
	}
};

