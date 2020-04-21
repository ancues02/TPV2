#pragma once

#include "ecs.h"
#include "StarsSystem.h"
#include "System.h"
#include "Score.h"
#include "AsteroidSystem.h"
//#include "GameState.h"
class GameCtrlSystem: public System {
public:

	GameCtrlSystem() :
		System(ecs::_sys_GameCtrl) {
	}

	void init() override {
		Entity *e = mngr_->addEntity();
		auto sc = e->addComponent<Score>();
		sc->points_ = 0;
		//e->addComponent<GameState>();
		mngr_->setHandler(ecs::_hdlr_GameState,e);
	}

	void update() override {
		auto ih = game_->getInputHandler();

		if ( ih->keyDownEvent() && ih->isKeyDown(SDLK_RETURN)) {
			mngr_->getSystem<AsteroidSystem>(ecs::_sys_Asteroids)->addAsteroids(10);
		}
	}



};

