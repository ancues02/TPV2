#include "BulletsPool.h"
BulletsPool::BulletsPool() :
	Component(ecs::BulletsPool),
	pool([](Bullet* o) {return o->inUse; })
{}

BulletsPool::~BulletsPool() {
}

void BulletsPool::init() {
	//generateAsteroids(10);
}

/*void AsteroidPool::update() {

	//for (auto& a : pool.getPool()) {
	//	a->pos_ = a->pos_ + a->vel;
	//}
}*/

void BulletsPool::disableAll() {
	for (auto& a : pool.getPool()) {
		a->inUse = false;
	}
}

//Desactiva la bala y activa dos asteroides con vel  diferente y pos parecida al asteroide padre
//bajamos uno a su generacion (si es 0 no crea)
/*void BulletsPool::onCollision(Bullet* a, AsteroidPool::Asteroid* b) {
	//b->inUse = false;
	a->inUse = false;
	
}*/


void BulletsPool::shoot(Vector2D pos, Vector2D vel, double w, double h) {
	Bullet* b = pool.getObj();
	if (b != nullptr) {
		b->pos_ = pos;
		b->vel = vel;
		b->width_ = w;
		b->height_ = h;
		b->rotation = (Vector2D(0, -1).angle(vel));
	}
}

std::vector<BulletsPool::Bullet*> BulletsPool::getPool() {
	return pool.getPool();
}
