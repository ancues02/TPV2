#pragma once
#include "System.h"
#include <cmath>
#include "SDL_macros.h"
#include "AsteroidPool.h"
#include "Manager.h"
#include "SDLGame.h"
#include "Health.h"
class FighterSystem : public System
{
private:
	Entity* fighter_;
	Transform* tr_;
public:
	FighterSystem() :
		System(ecs::_sys_Fighter),
		fighter_(nullptr),
		tr_(nullptr){
	}

	// - desactivar el asteroide “a” y crear 2 asteroides como en la práctica 1.
	void onCollisionWithAsteroid(Entity* a) {
		/*AsteroidLifeTime* aLT = a->getComponent<AsteroidLifeTime>(ecs::AsteroidLifeTime);
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

		}*/
	}

	void init() override {
		fighter_ = mngr_->addEntity();

		fighter_->addComponent<Transform>(Vector2D(game_->getWindowWidth() / 2, (game_->getWindowHeight() / 2) - 25), Vector2D( 0,0 ),50,50,0);
		fighter_->addComponent<Health>(3);
		fighter_->addComponent<ImageComponent>(game_->getTextureMngr()->getTexture(Resources::Airplanes));
		mngr_->setHandler(ecs::_hdlr_Fighter, fighter_);
	}

	void update() override {
		for (auto& e : mngr_->getGroupEntities(ecs::_grp_Asteroid)) {

			if (!e->isActive())
				return;

			Transform* tr = e->getComponent<Transform>(ecs::Transform);
			if (tr->position_.getX() > game_->getWindowWidth())
				tr->position_.setX(-tr->width_);
			else if (tr->position_.getX() + tr->width_ < 0)
				tr->position_.setX(game_->getWindowWidth());
			if (tr->position_.getY() > game_->getWindowHeight())
				tr->position_.setY(-tr->height_);
			else if (tr->position_.getY() + tr->height_ < 0)
				tr->position_.setY(game_->getWindowHeight());
			tr->rotation_ += 1;

			tr->position_ = tr->position_ + tr->velocity_;
		}
	}
};

