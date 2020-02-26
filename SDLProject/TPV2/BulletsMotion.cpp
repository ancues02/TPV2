#include "BulletsMotion.h"
#include "Entity.h"

//constructora
BulletsMotion::BulletsMotion() :
	Component(ecs::AsteroidsMotion), pool(nullptr) {
}

//destructora
BulletsMotion::~BulletsMotion() {
}

//inicializa el pool de balas
void BulletsMotion::init() {
	pool = GETCMP1_(BulletsPool);
}

//mueve las balas y las desactiva al salir de la ventana
void BulletsMotion::update() {
	for (auto& a : pool->getPool()) {
		if (a->inUse) {
			if (a->pos_.getX() > game_->getWindowWidth())
				a->inUse = false;
			else if (a->pos_.getX() + a->width_ < 0)
				a->inUse = false;
			else if (a->pos_.getY() > game_->getWindowHeight())
				a->inUse = false;
			else if (a->pos_.getY() + a->height_ < 0)
				a->inUse = false;
			else
				a->pos_ = a->pos_ + a->vel;
		}
	}
}