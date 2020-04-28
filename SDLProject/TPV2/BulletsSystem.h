#pragma once
#include "System.h"
#include "Vector2D.h"
#include "Entity.h"
#include "BulletPool.h"
#include "Manager.h"
#include "SDLGame.h"

class BulletsSystem : public System
{
public:
	BulletsSystem() :
		System(ecs::_sys_Bullets) {
	}


	void shoot(Vector2D pos, Vector2D vel, double width, double height);

	//desactiva la entidad b(una bala) 
	void onCollisionWithAsteroid(Entity* b, Entity* a) {
		b->setActive(false);
	}


	void update() override;

	//se desactivan todas las balas, se utiliza por ejemplo cuando te hacen daño
	void disableAll() {
		for (auto& e : mngr_->getGroupEntities(ecs::_grp_Bullet)) {
			e->setActive(false);
		}
	}
};

