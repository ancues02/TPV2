#include "Gun.h"
#include "InputHandler.h"
#include "Entity.h"
#include <iostream>
Gun::Gun() :
	Gun(SDLK_SPACE) {
}

Gun::Gun(SDL_Keycode shoot) :
	Component(ecs::Gun), //
	shoot(shoot),
	tr_(nullptr)//
{
}

Gun::~Gun() {
}

void Gun::init() {
	tr_ = GETCMP1_(Transform);
}

void Gun::update() {

	InputHandler* ih = InputHandler::instance();

	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(shoot)) {
			cout << "DISPAROOOOO";
		}
		

	}
}

