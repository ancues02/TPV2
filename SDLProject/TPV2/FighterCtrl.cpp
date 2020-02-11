#include "FighterCtrl.h"
#include "InputHandler.h"
#include "Entity.h"
#include "Transform.h"

FighterCtrl::FighterCtrl() :
	FighterCtrl(SDLK_LEFT, SDLK_RIGHT, SDLK_UP) {
}

FighterCtrl::FighterCtrl(SDL_Keycode rotateL, SDL_Keycode rotateR, SDL_Keycode move) :
		Component(ecs::FighterCtrl), //
		rotateLeft(rotateL), //
		rotateRight(rotateR), //
		move(move),
		tr_(nullptr)//
{
}

FighterCtrl::~FighterCtrl() {
}

void FighterCtrl::init() {
	tr_ = GETCMP1_(Transform);
}

void FighterCtrl::update() {

	InputHandler *ih = InputHandler::instance();

	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(rotateLeft)) {
			tr_->setRot(tr_->getRot() - 5);
		} else if (ih->isKeyDown(rotateRight)) {
			tr_->setRot(tr_->getRot() + 5);
		} else if (ih->isKeyDown(move)) {
			Vector2D newVel = tr_->getVel() + Vector2D(0, -1).rotate(tr_->getRot()) * 0.5;
			if (newVel.magnitude() > 2) newVel = newVel.normalize() * 2;
			tr_->setVel(newVel);
		}

	}
}

