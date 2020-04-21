#pragma once
#include "System.h"
#include "InputHandler.h"
#include "Manager.h"
#include "SDLGame.h"

#include "Transform.h"
#include "BulletsSystem.h"
class FigtherGunSystem : public System
{
private:
	Uint32 cd = 0;	//registra la ultima vez que se disparó
	size_t limitTime = 250;//tiempo entre cada dissparo minimo
	
public:
	FigtherGunSystem() :
		System(ecs::_sys_FighterGun)
		{}

	// - si el juego está parado no hacer nada.
	// - si el jugador pulsa SPACE, llamar a shoot(...) del BulletsSystem para añadir
	// una bala al juego -- se puede disparar sólo una bala cada 0.25sec.
	void update() override {
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
};

