#pragma once

#include "Component.h"
#include "Transform.h"

class FighterCtrl : public Component {
public:
	FighterCtrl();
	FighterCtrl(SDL_Keycode left, SDL_Keycode right, SDL_Keycode mov);
	virtual ~FighterCtrl();

	/*inline void setCtrlKeys(SDL_Keycode left, SDL_Keycode right,
			SDL_Keycode mov) {
		rotateLeft = left;
		rotateRight = right;
		move = mov;
	}*/

	void init() override;
	void update() override;

private:
	SDL_Keycode rotateLeft;
	SDL_Keycode rotateRight;
	SDL_Keycode move;
	Transform *tr_;
};

