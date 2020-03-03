#pragma once

#include "Component.h"
enum State {
	Stop, Running, Win, Lose
};
class ScoreManager: public Component {
public:
	ScoreManager();
	virtual ~ScoreManager();

	

	bool isRunning() const {
		return state == Running;
	}

	void setState(State newState) {
		state = newState;
	}
	State getState() {
		return state;
	}
	void addScore(int n) { score += n; }

	void resetScore() { score = 0; }

	int getScore() { return score; }

	bool isGameOver() {//ver si quedan asteroides o te quedan vidas
		return state == Win || state == Lose;
	}

private:
	State state = Stop;
	int score;
};
