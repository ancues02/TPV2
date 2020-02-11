#pragma once

#include "Component.h"
#include "Transform.h"

class FighterCtrl : public Component {
public:
	FighterCtrl();
	FighterCtrl(SDL_Keycode up, SDL_Keycode down, SDL_Keycode stop);
	virtual ~FighterCtrl();

	inline void setCtrlKeys(SDL_Keycode up, SDL_Keycode down,
			SDL_Keycode stop) {
		rotateLeft = up;
		rotateRight = down;
		move = stop;
	}

	void init() override;
	void update() override;

private:
	SDL_Keycode rotateLeft;
	SDL_Keycode rotateRight;
	SDL_Keycode move;
	Transform *tr_;
};

