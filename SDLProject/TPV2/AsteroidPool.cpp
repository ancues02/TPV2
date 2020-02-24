#include "AsteroidPool.h"
void AsteroidPool::generateAsteroids(int n) {
	SRandBasedGenerator random;
	random.init();
	Vector2D p(0,0 );
	switch (random.nextInt(0, 4)) {
	case 0://left
		p.setY(random.nextInt(0, game_->getWindowHeight()));//= (double)random.nextInt(0, game_->getWindowHeight());
		break;
	case 1://up
		p.setX (random.nextInt(0, game_->getWindowWidth()));
		break;
	case 2://Right
		p.setY( random.nextInt(0, game_->getWindowHeight()));
		p.setX(game_->getWindowWidth());
		break;
	case 3://bottom
		p.setX(random.nextInt(0, game_->getWindowWidth()));
		p.setY( game_->getWindowHeight());
		break;
	}
	Vector2D c(0, 0);
	int rx = random.nextInt(-50, 50),
		ry = random.nextInt(-50, 50);
	c.setX(game_->getWindowWidth / 2 +rx);
	c.setY(game_->getWindowHeight / 2 +ry);
	
	Vector2D vel = (c - p).normalize() * (random.nextInt(0, 10) / 10.0);
}

AsteroidPool::AsteroidPool() :
	Component(ecs::AsteroidPool),
	pool([](Asteroid* o) {return o->inUse; })
{}
	
AsteroidPool::~AsteroidPool() {
}

void AsteroidPool::init() {
	
}

void AsteroidPool::update() {

	
}