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

	void update() {
		auto ptr = mngr_->getHandler(ecs::_hdlr_Fighter)->getComponent<Transform>(ecs::Transform);
		for( auto& a : mngr_->getGroupEntities(ecs::_grp_Asteroid)) {
			if (a->isActive()) {
				auto atr = a->getComponent<Transform>(ecs::Transform);
				if (Collisions::collides(ptr->position_, ptr->width_, ptr->height_, atr->position_, atr->width_, atr->height_)) {
					mngr_->getSystem<FighterSystem>(ecs::_sys_Fighter)->onCollisionWithAsteroid(a);
					break;
				}
				//recorremos las balas y si chocan con asteroides llamamos a sus onCollision
				for (auto& b : mngr_->getGroupEntities(ecs::_grp_Bullet)) {
					if (!b->isActive()) continue;//salta esta interaccion si la bala no esta activa
					//if (!a->isActive()) break;
					auto btr = b->getComponent<Transform>(ecs::Transform);

					if (Collisions::collides(btr->position_, btr->width_, btr->height_, atr->position_, atr->width_, atr->height_)) {
						mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<Score>(ecs::Score)->points_++;
						mngr_->getSystem<BulletsSystem>(ecs::_sys_Bullets)->onCollisionWithAsteroid(b, a);
						mngr_->getSystem<AsteroidSystem>(ecs::_sys_Asteroids)->onCollisionWithBullet(a, b);

					}
				}
			}
		}
	}
};

