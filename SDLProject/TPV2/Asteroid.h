#pragma once
#include "Entity.h"

class Asteroid: public Entity
{
public:
	Asteroid(SDLGame* game, EntityManager* mngr) :Entity(  game,   mngr){ };
	virtual ~Asteroid() {};
	bool inUse=false;
private:
	Vector2D pos = { 0,0 }, vel = { 0,0 };
	double width=0, height=0, rotation=0;
	int gen = 0;

};

