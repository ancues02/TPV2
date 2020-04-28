#include "BulletsSystem.h"

//se crea una nueva bala
void BulletsSystem::shoot(Vector2D pos, Vector2D vel, double width, double height)
{
	double rotation = (Vector2D(0, -1).angle(vel));

	//game_->getAudioMngr()->playChannel(Resources::GunShot, 0, 0);
	Entity* e = mngr_->addEntity<BulletPool>(pos, vel, width, height, rotation);
	if (e != nullptr) {
		e->addToGroup(ecs::_grp_Bullet);
		game_->getAudioMngr()->playChannel(Resources::GunShot, 0, 0);
	}
}

//se actualiza su posicion y si se sale de los limites se desactiva 
void BulletsSystem::update()
{
	for (auto& e : mngr_->getGroupEntities(ecs::_grp_Bullet)) {
		if (!e->isActive())
			return;
		Transform* tr = e->getComponent<Transform>(ecs::Transform);
		tr->position_ = tr->position_ + tr->velocity_;
		if (tr->position_.getX() > game_->getWindowWidth())
			e->setActive(false);
		else if (tr->position_.getX() + tr->width_ < 0)
			e->setActive(false);
		else if (tr->position_.getY() > game_->getWindowHeight())
			e->setActive(false);
		else if (tr->position_.getY() + tr->height_ < 0)
			e->setActive(false);
		
			


	}
}
