#include "BulletsPool.h"
#include "AsteroidPool.h"

//Pasa la funcion lambda al objectPool
BulletsPool::BulletsPool() :
	Component(ecs::BulletsPool),
	pool([](Bullet* o) {return o->inUse; })

{}

BulletsPool::~BulletsPool() {
}

void BulletsPool::init() {
}

//Desactiva todas las balas (las marca como no usadas)
void BulletsPool::disableAll() {
	for (auto& a : pool.getPool()) {
		a->inUse = false;
	}
}

//Desactiva la bala cuando colisiona con un asteroide
void BulletsPool::onCollision(Bullet* a, Asteroid* b) {
	a->inUse = false;
}

//Añade una bala a la escena
void BulletsPool::shoot(Vector2D pos, Vector2D vel, double w, double h) {
	Bullet* b = pool.getObj();
	if (b != nullptr) {
		b->pos_ = pos;
		b->vel = vel;
		b->width_ = w;
		b->height_ = h;
		b->rotation = (Vector2D(0, -1).angle(vel));
		b->inUse = true;
		game_->getAudioMngr()->playChannel(Resources::GunShot, 0, 0);
	}
}

std::vector<Bullet*> BulletsPool::getPool() {
	return pool.getPool();
}
