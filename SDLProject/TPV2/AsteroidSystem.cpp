#include "AsteroidSystem.h"
#include "GameCtrlSystem.h"

void AsteroidSystem::onCollisionWithBullet(Entity* a, Entity* b)
{
	a->setActive(false);
	AsteroidLifeTime* aLT = a->getComponent<AsteroidLifeTime>(ecs::AsteroidLifeTime);
	Transform* aTR = a->getComponent<Transform>(ecs::Transform);
	if (aLT->gen_ > 0) {
		Vector2D vel = aTR->velocity_.rotate((double)aLT->gen_ * 45);
		int newGen = aLT->gen_ - 1;
		Vector2D pos = aTR->position_ + vel.normalize();
		Vector2D pos2 = aTR->position_ - vel.normalize();
		double rotation = game_->getRandGen()->nextInt(0, 361);
		double rotation2 = game_->getRandGen()->nextInt(0, 361);
		double width = 10 + 3 * newGen;
		double height = width;

		Entity* a1 = mngr_->addEntity<AsteroidPool>(pos, vel, width, height, rotation, newGen);
		if (a1 != nullptr)
			a1->addToGroup(ecs::_grp_Asteroid);
		Entity* a2 = mngr_->addEntity<AsteroidPool>(pos2, (vel * -1), width, height, rotation2, newGen);
		if (a2 != nullptr)
			a2->addToGroup(ecs::_grp_Asteroid);
		numOfAsteroids_ += 1;
	}
	else {

		if (--numOfAsteroids_ <= 0) {
			mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->onAsteroidsExtenction();
		}
	}
}
