#pragma once

#include "ecs.h"
#include "System.h"
#include "SDLGame.h"
#include "Manager.h"

class GameCtrlSystem: public System {
public:
	enum State : uint8_t {
		READY, RUNNING, ROUNDOVER, GAMEOVER
	};

	GameCtrlSystem();
	void init() override;
	void update() override;
	void recieve(const msg::Message& msg) override;
	State getState() {
		return state_;
	}
	void onFighterDeath(uint8_t fighterId);
	void bothFighterCollision();
	uint8_t getScore(uint8_t fighterId) {
		assert(fighterId >= 0 && fighterId <= 1);
		return score[fighterId];
	}
private:
	void resetScore();
	void startGame();
	void sendMyInfo();

	uint8_t score[2];
	State state_;
};

