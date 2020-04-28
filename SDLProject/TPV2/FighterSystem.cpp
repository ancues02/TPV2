#include "FighterSystem.h"
#include "GameCtrlSystem.h"

//Crea el caza con sus componentes correspondientes y lo establece como handler
void FighterSystem::init() {
	fighter_ = mngr_->addEntity();

	tr_ = fighter_->addComponent<Transform>(Vector2D(game_->getWindowWidth() / 2, (game_->getWindowHeight() / 2) - 25.0), Vector2D(0, 0), 50, 50, 0);
	fighter_->addComponent<Health>(3);
	fighter_->addComponent<ImageComponent>(game_->getTextureMngr()->getTexture(Resources::Airplanes));
	mngr_->setHandler(ecs::_hdlr_Fighter, fighter_);
}

//Mueve el caza según el input y realiza el rebote con los limites de la pantalla
void FighterSystem::update(){
	//Comprueba el input
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

	//mueve el caza
	Vector2D v = tr_->position_ + tr_->velocity_;
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

//Baja la vida del caza, restablece su posicion en el centro y le dice al 
//sistema de contol que el caza ha muerto
void FighterSystem::onCollisionWithAsteroid(Entity* a) {

	Health* health = fighter_->getComponent<Health>(ecs::Health);
	health->health_ = max(health->health_ - 1, 0);

	resetPosition();

	mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->onFighterDeath();
}

//Devuelve al caza su posicion central
void FighterSystem::resetPosition()
{
	Transform* tr = fighter_->getComponent<Transform>(ecs::Transform);
	tr->velocity_ = { 0,0 };
	tr->rotation_ = 0;
	tr->position_ = Vector2D(game_->getWindowWidth() / 2, (game_->getWindowHeight() / 2) - 25.0);
}