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

	// - añadir una bala al juego, como en la práctica 1 pero usando entidades.
// - no olvidar añadir la bala al grupo _grp_Bullet
	void shoot(Vector2D pos, Vector2D vel, double width, double height) {
		
		double rotation = (Vector2D(0, -1).angle(vel));
	
		Entity* e = mngr_->addEntity<BulletPool>(pos, vel, width, height, rotation);
		if (e != nullptr) {
			e->addToGroup(ecs::_grp_Bullet);
			game_->getAudioMngr()->playChannel(Resources::GunShot, 0, 0);
		}
	}
		// - desactivar la bala “b”
	void onCollisionWithAsteroid(Entity* b, Entity* a) {
		b->setActive(false);
	}
		// - si el juego está parado no hacer nada.
		// - mover las balas y desactivar las que se salen de la ventana
	void update() override {
		for (auto& e : mngr_->getGroupEntities(ecs::_grp_Bullet)) {
			if(!e->isActive())
				return;
			Transform* tr = e->getComponent<Transform>(ecs::Transform);
			
				if (tr->position_.getX() > game_->getWindowWidth())
					e->setActive( false);
				else if (tr->position_.getX() + tr->width_ < 0)
					e->setActive(false);
				else if (tr->position_.getY() > game_->getWindowHeight())
					e->setActive(false);
				else if (tr->position_.getY() + tr->height_ < 0)
					e->setActive(false);
				else
					tr->position_ = tr->position_ + tr->velocity_;
				
			
		}
	}
	void disableAll() {
		for (auto& e : mngr_->getGroupEntities(ecs::_grp_Bullet)) {
			e->setActive(false);
		}
	}
};

