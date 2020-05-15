#include "GameCtrlSystem.h"

#include <cassert>
#include <cstdint>
#include "ecs.h"
#include "Entity.h"
#include "FighterInfo.h"
#include "FightersSystem.h"
#include "Manager.h"

using ecs::CmpId;

GameCtrlSystem::GameCtrlSystem() :
		System(ecs::_sys_GameCtrl) {
	state_ = READY;
	resetScore();
}

void GameCtrlSystem::recieve(const msg::Message& msg) {
	switch (msg.id) {
		case msg::_PLAYER_INFO: {
			if (msg.senderClientId == mngr_->getClientId())
				return;
			state_ = RUNNING;
			mngr_->send<msg::Message>(msg::_PLAYER_INFO);
			break;
		}
		case msg::_CLIENT_DISCONNECTED: {
			state_ = READY;
			mngr_->getSystem<FightersSystem>(ecs::_sys_Fighters)->resetFighterPositions();
			resetScore();
			break;
		}
		case msg::_START_REQ: {
			if (state_ != RUNNING)
				mngr_->send<msg::Message>(msg::_START_GAME);	//posicionar players?	
			break;
		}
		case msg::_START_GAME: {
			startGame();
			break;
		}
		default:
			break;
	}
}

void GameCtrlSystem::init() {
	state_ = READY;
	mngr_->send<msg::Message>(msg::_PLAYER_INFO);
}

void GameCtrlSystem::update() {
	if (state_ != RUNNING) {
		InputHandler *ih = game_->getInputHandler();
		if (ih->keyDownEvent() && ih->isKeyDown(SDLK_RETURN)) {
			startGame();
		}
	}
}

void GameCtrlSystem::startGame() {
	if (state_ == GAMEOVER) {
		resetScore();
	}
	mngr_->getSystem<FightersSystem>(ecs::_sys_Fighters)->resetFighterPositions();	//cambiar de sitio a fighterSystem
	state_ = RUNNING;
}

void GameCtrlSystem::onFighterDeath(uint8_t fighterId) {
	assert(fighterId >= 0 && fighterId <= 1);

	uint8_t id = 1 - fighterId; // the id of the other player fighter

	state_ = ROUNDOVER;
	score[id]++;
	if (score[id] == 3)
		state_ = GAMEOVER;

}

void GameCtrlSystem::resetScore() {
	score[0] = score[1] = 0;
}
