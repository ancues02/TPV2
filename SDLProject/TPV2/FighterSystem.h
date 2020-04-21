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

	// - poner el caza en el centro con velocidad 0 y rotación 0. No hace falta
	// desactivar la entidad (no dibujarla si el juego está parado en RenderSystem).
	void onCollisionWithAsteroid(Entity* a) {
		
		Health* health = fighter_->getComponent<Health>(ecs::Health);
		health->health_ = max(health->health_ - 1, 0);
		/*if (health->health_ <= 0) {
			game_->getAudioMngr()->playMusic(Resources::Boooo, 0);
			scoreManager_->setState(Lose);
		}
		else {
			scoreManager_->setState(Stop);
			game_->getAudioMngr()->haltMusic();
		}*/
		Transform* tr = fighter_->getComponent<Transform>(ecs::Transform);
		tr->velocity_ = { 0,0 };
		tr->rotation_ = 0;
		tr->position_ = Vector2D( game_->getWindowWidth() / 2, (game_->getWindowHeight() / 2) - 25.0 );
		
	}

	void init() override {
		fighter_ = mngr_->addEntity();

		tr_ = fighter_->addComponent<Transform>(Vector2D(game_->getWindowWidth() / 2, (game_->getWindowHeight() / 2) - 25.0), Vector2D( 0,0 ),50,50,0);
		fighter_->addComponent<Health>(3);
		fighter_->addComponent<ImageComponent>(game_->getTextureMngr()->getTexture(Resources::Airplanes));
		mngr_->setHandler(ecs::_hdlr_Fighter, fighter_);
	}

	void update() override {
		//Checks input
		InputHandler* ih = InputHandler::instance();
		if (ih->keyDownEvent()) {
			if (ih->isKeyDown(SDLK_LEFT)) {
				tr_->rotation_ -= 5;
			}
			else if (ih->isKeyDown(SDLK_RIGHT)) {
				tr_->rotation_ += 5;
			}
			else if (ih->isKeyDown(SDLK_UP)) {
				Vector2D newVel = tr_->velocity_ + Vector2D(0, -1).rotate(tr_->rotation_) * 0.5;
				if (newVel.magnitude() > 2) newVel = newVel.normalize() * 2;
				tr_->velocity_ = newVel;
			}
		}

		//Moves fighter
		Vector2D v = tr_->position_+ tr_->velocity_;
		double y = v.getY();
		double x = v.getX();

		//comprobar limites y rebotes
		if (y <= 0) {
			v.setY(0);
			tr_->velocity_.setY(-tr_->velocity_.getY());
		}
		else if (y + tr_->height_ >= game_->getWindowHeight()) {
			v.setY(game_->getWindowHeight() - tr_->height_);
			tr_->velocity_.setY(-tr_->velocity_.getY());
		}
		if (x <= 0) {
			v.setX(0);
			tr_->velocity_.setX(-tr_->velocity_.getX());
		}
		else if (x + tr_->width_ >= game_->getWindowWidth()) {
			v.setX(game_->getWindowWidth() - tr_->width_);
			tr_->velocity_.setX(-tr_->velocity_.getX());
		}
		tr_->velocity_ = tr_->velocity_ * 0.995;
		tr_->position_ = v;
	}
};

