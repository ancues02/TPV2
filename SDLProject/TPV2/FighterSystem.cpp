#include "FighterSystem.h"
#include "GameCtrlSystem.h"

void FighterSystem::onCollisionWithAsteroid(Entity* a) {

	Health* health = fighter_->getComponent<Health>(ecs::Health);
	health->health_ = max(health->health_ - 1, 0);

	resetPosition();

	mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->onFighterDeath();
}

void FighterSystem::resetPosition()
{
	Transform* tr = fighter_->getComponent<Transform>(ecs::Transform);
	tr->velocity_ = { 0,0 };
	tr->rotation_ = 0;
	tr->position_ = Vector2D(game_->getWindowWidth() / 2, (game_->getWindowHeight() / 2) - 25.0);
}

