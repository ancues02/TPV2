#include "CollisionSystem.h"

#include "Collisions.h"
#include "BulletsSystem.h"
#include "FighterInfo.h"
#include "GameCtrlSystem.h"
#include "Transform.h"
#include "Manager.h"

CollisionSystem::CollisionSystem() :
		System(ecs::_sys_Collision) {
}

CollisionSystem::~CollisionSystem() {
}

void CollisionSystem::recieve(const msg::Message& msg)
{
	switch (msg.id) {
	case msg::_BULLET_FIGHTER_COLLISION: {
		mngr_->getSystem<BulletsSystem>(ecs::_sys_Bullets)->disableAll();
		mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->onFighterDeath(static_cast<const msg::BulletFighterCollisionMsg&>(msg).fighter_id);
	}

	default:
		break;
	}
}

void CollisionSystem::update() {
	auto gameCtrlSys = mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl);

	if (gameCtrlSys->getState() != GameCtrlSystem::RUNNING || mngr_->getClientId() != 0)	//solo comprueba las colisiones el cliente 0
		return;	

	for (auto &f : mngr_->getGroupEntities(ecs::_grp_Fighters)) {
		auto fTR = f->getComponent<Transform>(ecs::Transform);

		for (auto &b : mngr_->getGroupEntities(ecs::_grp_Bullets)) {
			if (!b->isActive())
				continue;

			auto bTR = b->getComponent<Transform>(ecs::Transform);

			if (Collisions::collidesWithRotation(bTR->position_, bTR->width_,
					bTR->height_, bTR->rotation_, fTR->position_, fTR->width_,
					fTR->height_, fTR->rotation_)) {
				mngr_->send<msg::BulletFighterCollisionMsg>(f->getComponent<FighterInfo>(ecs::FighterInfo)->fighterId);
			}
		}
	}	
}

