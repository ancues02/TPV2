#pragma once
#include "System.h"
#include <cmath>
#include "SDL_macros.h"
#include "AsteroidPool.h"
#include "Manager.h"
#include "SDLGame.h"

class AsteroidSystem : public System
{
private:
	std::size_t numOfAsteroids_ = 0;
public:
	AsteroidSystem() :
		System(ecs::_sys_Asteroids) {
	}

	// - desactivar el asteroide “a” y crear 2 asteroides como en la práctica 1.
	void onCollisionWithBullet(Entity* a, Entity* b);


	void addAsteroids(int n) {
		numOfAsteroids_ = 1;
		for (auto i = 0; i < 1; i++) {
			Vector2D p(0, 0);
			switch (game_->getRandGen()->nextInt(0, 4)) {
			case 0://left
				p.setY(game_->getRandGen()->nextInt(1, game_->getWindowHeight()));//= (double)random.nextInt(0, game_->getWindowHeight());

				break;
			case 1://up
				p.setX(game_->getRandGen()->nextInt(1, game_->getWindowWidth()));

				break;
			case 2://Right
				p.setY(game_->getRandGen()->nextInt(1, game_->getWindowHeight()));
				p.setX(game_->getWindowWidth());

				break;
			case 3://bottom
				p.setX(game_->getRandGen()->nextInt(1, game_->getWindowWidth()));
				p.setY(game_->getWindowHeight());
				break;
			}
			Vector2D c(0, 0);
			double rx = game_->getRandGen()->nextInt(-50, 51),
				ry = game_->getRandGen()->nextInt(-50, 51);
			c.setX(game_->getWindowWidth() / 2 + rx);
			c.setY(game_->getWindowHeight() / 2 + ry);

			Vector2D vel = (c - p).normalize() * (game_->getRandGen()->nextInt(1, 11)) / 10;
			int gen = game_->getRandGen()->nextInt(1, 3);
			double w = 10 + 3 * gen;
			double h = w;
			double rotation = game_->getRandGen()->nextInt(0, 361);

			Entity* e = mngr_->addEntity<AsteroidPool>(p, vel, w, h, rotation, gen);
			if (e != nullptr)
				e->addToGroup(ecs::_grp_Asteroid);
		}
	}

	void update() override {
		for (auto& e : mngr_->getGroupEntities(ecs::_grp_Asteroid)) {

			if (!e->isActive())
				return;

			Transform* tr = e->getComponent<Transform>(ecs::Transform);
			if(tr->position_.getX() > game_->getWindowWidth())
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

	void disableAll() {
		for (auto& e : mngr_->getGroupEntities(ecs::_grp_Asteroid)) {
			e->setActive(false);
		}
	}
};

