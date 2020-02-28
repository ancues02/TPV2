#include "Gun.h"
#include "InputHandler.h"
#include "Entity.h"
#include <iostream>
Gun::Gun() :
	Gun(SDLK_SPACE, nullptr) {
}

Gun::Gun(SDL_Keycode shoot, BulletsPool* bulletPool) :
	Component(ecs::Gun), //
	shoot(shoot),
	tr_(nullptr),//
	b_pool(bulletPool)
{
}

Gun::~Gun() {
}

void Gun::init() {
	tr_ = GETCMP1_(Transform);
	//b_pool = GETCMP1_(BulletsPool);
}

void Gun::update() {
	
	InputHandler* ih = InputHandler::instance();

	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(shoot) && game_->getTime() - cd >= limitTime) {
			cd = game_->getTime();
			Vector2D bulletPos = tr_->getPos() + Vector2D(tr_->getW() / 2, tr_->getH() / 2) + Vector2D(0, -(tr_->getH() / 2 + 5.0)).rotate(tr_->getRot());
			Vector2D bulletVel = Vector2D(0, -1).rotate(tr_->getRot()) * 2;
			b_pool->shoot(bulletPos, bulletVel, 2,15);

		}
		

	}
}

