#include "GameCtrlSystem.h"

#include <cassert>
#include <cstdint>
#include "ecs.h"
#include "Entity.h"
#include "FighterInfo.h"
#include "FightersSystem.h"
#include "Manager.h"
#include "PlayerName.h"

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
			if (state_ == READY) {
				state_ = ROUNDOVER;
				mngr_->send<msg::Message>(msg::_PLAYER_INFO);
			}
			break;
		}
		case msg::_CLIENT_DISCONNECTED: {
			state_ = READY;
			mngr_->getSystem<FightersSystem>(ecs::_sys_Fighters)->resetFighterPositions();
			resetScore();
			PlayerName* p_name;
			if (static_cast<const msg::ClientDisconnectedMsg&>(msg).clientId == 0) {
				p_name = mngr_->getHandler(ecs::_hdlr_Fighter0)->getComponent<PlayerName>(ecs::PlayerName);
				cout << "P0 disconnected" << endl;
			}
			else {
				p_name = mngr_->getHandler(ecs::_hdlr_Fighter1)->getComponent<PlayerName>(ecs::PlayerName);
				cout << "P1 disconnected" << endl;
			}
			p_name->setted_ = false;
			strcpy_s(&p_name->name_[0], 11, "Not Ready");
			break;
		}
		//si el juego no esta en marcha, quiero pedir que se inicie
		case msg::_START_REQ: {
			if (state_ != RUNNING)
				mngr_->send<msg::Message>(msg::_START_GAME);
			break;
		}
		case msg::_START_GAME: {	
			startGame();
			break;
		}
		case msg::_PLAYER_NAME: {
			if (msg.senderClientId == mngr_->getClientId())
				return;
			PlayerName* p_name0 = mngr_->getHandler(ecs::_hdlr_Fighter0)->getComponent<PlayerName>(ecs::PlayerName);
			PlayerName* p_name1 = mngr_->getHandler(ecs::_hdlr_Fighter1)->getComponent<PlayerName>(ecs::PlayerName);

			if (mngr_->getClientId() == 0 && !p_name1->setted_) {
				strcpy_s(&p_name1->name_[0], 11, static_cast<const msg::PlayerNameMsg&>(msg).name_);
				mngr_->send<msg::PlayerNameMsg>(mngr_->getName());
				p_name1->setted_ = true;
			}
			else if (mngr_->getClientId() == 1 && !p_name0->setted_) {
				strcpy_s(&p_name0->name_[0], 11, static_cast<const msg::PlayerNameMsg&>(msg).name_);
				p_name0->setted_ = true;
				mngr_->send<msg::PlayerNameMsg>(mngr_->getName());
			}
			break;
		}
		default:
			break;
	}
}

void GameCtrlSystem::init() {
	state_ = READY;
	mngr_->send<msg::Message>(msg::_PLAYER_INFO);
	
	PlayerName* p_name; 
	
	if (mngr_->getClientId() == 0) {
		p_name = mngr_->getHandler(ecs::_hdlr_Fighter0)->getComponent<PlayerName>(ecs::PlayerName);
	}
	else {
		p_name = mngr_->getHandler(ecs::_hdlr_Fighter1)->getComponent<PlayerName>(ecs::PlayerName);
	}
	strcpy_s(&p_name->name_[0], 11, mngr_->getName());
	p_name->setted_ = true;
	mngr_->send<msg::PlayerNameMsg>(mngr_->getName());
}

void GameCtrlSystem::update() {
	if (state_ != RUNNING) {
		InputHandler *ih = game_->getInputHandler();
		if (ih->keyDownEvent() && ih->isKeyDown(SDLK_RETURN)) {
			mngr_->send<msg::Message>(msg::_START_REQ);
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

void GameCtrlSystem::bothFighterCollision()
{
	state_ = ROUNDOVER;

}



void GameCtrlSystem::resetScore() {
	score[0] = score[1] = 0;
}
