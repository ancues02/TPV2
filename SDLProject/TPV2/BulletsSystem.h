#pragma once
#include "System.h"
#include "Vector2D.h"
#include "Entity.h"
#include "BulletPool.h"
class BulletsSystem : public System
{
	// - añadir una bala al juego, como en la práctica 1 pero usando entidades.
// - no olvidar añadir la bala al grupo _grp_Bullet
	void shoot(Vector2D pos, Vector2D vel, double width, double height) {
		//Bullet* b = pool.getObj();
		if (b != nullptr) {
			b->pos_ = pos;
			b->vel = vel;
			b->width_ = w;
			b->height_ = h;
			b->rotation = (Vector2D(0, -1).angle(vel));
			b->inUse = true;
			game_->getAudioMngr()->playChannel(Resources::GunShot, 0, 0);
		}
		Entity* e = mngr_->addEntity<BulletPool>(pos, vel, width, height, rotation);
		if (e != nullptr)
			e->addToGroup(ecs::_grp_Asteroid);
	}
		// - desactivar la bala “b”
	void onCollisionWithAsteroid(Entity* b, Entity* a) {
		b->setActive(false);
	}
		// - si el juego está parado no hacer nada.
		// - mover las balas y desactivar las que se salen de la ventana
	void update() override {

	}
};

