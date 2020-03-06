#pragma once

#include "Component.h"
#include "Transform.h"

class FighterCtrl : public Component {
public:
	FighterCtrl();
	FighterCtrl(SDL_Keycode left, SDL_Keycode right, SDL_Keycode mov);
	virtual ~FighterCtrl();

	void init() override;
	void update() override;

private:
	SDL_Keycode rotateLeft;
	SDL_Keycode rotateRight;
	SDL_Keycode move;
	Transform *tr_;
};

