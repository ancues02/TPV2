#pragma once
#include "ecs.h"
#include "Manager.h"
#include "ImageComponent.h"
#include "SDL_macros.h"
#include "SDLGame.h"
#include "System.h"
#include "Transform.h"
#include "Entity.h"
#include "Score.h"
#include "Texture.h"
#include "Health.h"
#include "GameState.h"
class RenderSystem: public System {
public:
	RenderSystem() :
			System(ecs::_sys_Render) {
	}

	void draw(Entity* e);

	void drawScore();

	void drawFighter(Entity* e);

	
	void drawHealth();

	void update() override;
};

