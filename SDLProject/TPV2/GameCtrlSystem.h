#pragma once

#include "ecs.h"
#include "System.h"
#include "Score.h"
#include "AsteroidSystem.h"
#include "GameState.h"
#include "BulletsSystem.h"
#include "FighterSystem.h"

class GameCtrlSystem: public System {
public:

	GameCtrlSystem() :
		System(ecs::_sys_GameCtrl) {
	}

	void init() override {
		Entity *e = mngr_->addEntity();
		auto sc = e->addComponent<Score>();
		sc->points_ = 0;
		e->addComponent<GameState>();
		mngr_->setHandler(ecs::_hdlr_GameState,e);
	}

	void update() override {
		auto ih = game_->getInputHandler();
		auto gh = mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<GameState>(ecs::GameState);
		if (InputHandler::instance()->keyDownEvent()) {
			// Reinicia la puntuacion si termina el juego
			if (gh->currentState==gh->Lose || gh->currentState == gh->Win) {
				auto fighter = mngr_->getHandler(ecs::_hdlr_Fighter)->getComponent<Health>(ecs::Health);
				fighter->health_ = fighter->init_Health_;
				auto score = mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<Score>(ecs::Score);
				score->points_ = 0;
			
			}
			if (gh->currentState != gh->Running) {
				gh->currentState=gh->Running;
				game_->getAudioMngr()->playMusic(Resources::Imperial);
				mngr_->getSystem<AsteroidSystem>(ecs::_sys_Asteroids)->addAsteroids(10);
			}
		}
		
	}
	// - actualizar los componentes correspondientes (Score, Heath, GameState, …).
	void onFighterDeath() {
		
		mngr_->getSystem<AsteroidSystem>(ecs::_sys_Asteroids)->disableAll();
		mngr_->getSystem<BulletsSystem>(ecs::_sys_Bullets)->disableAll();

		auto gh = mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<GameState>(ecs::GameState);
		Health* fighterHealth=mngr_->getHandler(ecs::_hdlr_Fighter)->getComponent<Health>(ecs::Health);
		if (fighterHealth->health_ <= 0) {
			game_->getAudioMngr()->playMusic(Resources::Boooo, 0);
			gh->currentState = gh->Lose;
		}
		else {
			game_->getAudioMngr()->playChannel(Resources::Explosion, 0, 1);
			gh->currentState = gh->Stop;
			game_->getAudioMngr()->haltMusic();
		} 

	}
	
	void onAsteroidsExtenction() {
		mngr_->getSystem<BulletsSystem>(ecs::_sys_Bullets)->disableAll();
		mngr_->getSystem<FighterSystem>(ecs::_sys_Fighter)->resetPosition();
		auto gh = mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<GameState>(ecs::GameState);
		game_->getAudioMngr()->playMusic(Resources::Cheer, 0);
		gh->currentState = gh->Win;
	}
};

