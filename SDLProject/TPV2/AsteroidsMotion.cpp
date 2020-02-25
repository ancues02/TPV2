#include "AsteroidsMotion.h"
#include "Entity.h"



AsteroidsMotion::AsteroidsMotion() :
	Component(ecs::AsteroidsMotion),pool(nullptr) {
}

AsteroidsMotion::~AsteroidsMotion() {
}

void AsteroidsMotion::init() {
	pool = GETCMP1_(AsteroidPool);
}
void AsteroidsMotion::update() {
	for (auto& a : pool->getPool()) {
		if (a->pos_.getX() > game_->getWindowWidth())
			a->pos_.setX(-a->width_);
		else if (a->pos_.getX() + a->width_ < 0)
			a->pos_.setX(game_->getWindowWidth());
		if (a->pos_.getY() > game_->getWindowHeight())
			a->pos_.setY(-a->height_);
		else if (a->pos_.getY() + a->height_ < 0)
			a->pos_.setY(game_->getWindowHeight());
		a->rotation += 0.5;
		a->pos_ = a->pos_ + a->vel;
	}
}