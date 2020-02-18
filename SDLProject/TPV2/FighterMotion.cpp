#include "FighterMotion.h"
#include "Entity.h"



FighterMotion::FighterMotion() :
	Component(ecs::PaddleMoveBehaviour), tr_(nullptr) {
}

FighterMotion::~FighterMotion() {
}

void FighterMotion::init() {
	tr_ = GETCMP1_(Transform);
}

void FighterMotion::update() {

	Vector2D v = tr_->getPos() + tr_->getVel();
	//v = v * 0.9;
	double y = v.getY();
	double x = v.getX();

	if (y <= 0) {
		v.setY(0);
		tr_->setVelY(-tr_->getVel().getY());
	}
	else if (y + tr_->getH() >= game_->getWindowHeight()) {
		v.setY(game_->getWindowHeight() - tr_->getH());
		tr_->setVelY(-tr_->getVel().getY());
	}
	if (x <= 0) {
		v.setX(0);
		tr_->setVelX(-tr_->getVel().getX());
	}
	else if (x + tr_->getW() >= game_->getWindowWidth()) {
		v.setX(game_->getWindowWidth() - tr_->getW());

		tr_->setVelX(-tr_->getVel().getX());
	}
	tr_->setVel(tr_->getVel() * 0.995);
	tr_->setPos(v);
}