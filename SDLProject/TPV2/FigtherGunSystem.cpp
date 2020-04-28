#include "FigtherGunSystem.h"

//comprobamos si se dispara si se puede disparar, es decir, pasa un tiempo minimo entre un disparo y otro
void FigtherGunSystem::update()
{
	InputHandler* ih = InputHandler::instance();
	if (ih->keyDownEvent()) {

		if (ih->isKeyDown(SDLK_SPACE) && game_->getTime() - cd >= limitTime) {
			Transform* tr_ = mngr_->getHandler(ecs::_hdlr_Fighter)->getComponent<Transform>(ecs::Transform);
			BulletsSystem* bSystem = mngr_->getSystem< BulletsSystem>(ecs::_sys_Bullets);
			cd = game_->getTime();
			Vector2D bulletPos = tr_->position_ + Vector2D(tr_->width_ / 2, tr_->height_ / 2) + Vector2D(0, -(tr_->height_ / 2 + 5.0)).rotate(tr_->rotation_);
			Vector2D bulletVel = Vector2D(0, -1).rotate(tr_->rotation_) * 2;
			bSystem->shoot(bulletPos, bulletVel, 2, 15);
		}
	}
}
