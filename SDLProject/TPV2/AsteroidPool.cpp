#include "AsteroidPool.h"
#include "BulletsPool.h"

//creacion y activacion de n asteroides en posiciones aleatorias con velocidades aleatorias
void AsteroidPool::generateAsteroids(int n) {

	for (int i = 0; i < n; i++) {
		Asteroid* a = pool.getObj();
		if (a != nullptr) {
			
			Vector2D p(0, 0);
			switch (game_->getRandGen()->nextInt(0, 4)) {
			case 0://left
				p.setY(game_->getRandGen()->nextInt(1, game_->getWindowHeight()));//= (double)random.nextInt(0, game_->getWindowHeight());

				break;
			case 1://up
				p.setX(game_->getRandGen()->nextInt(1, game_->getWindowWidth()));

				break;
			case 2://Right
				p.setY(game_->getRandGen()->nextInt(1, game_->getWindowHeight()));
				p.setX(game_->getWindowWidth());

				break;
			case 3://bottom
				p.setX(game_->getRandGen()->nextInt(1, game_->getWindowWidth()));
				p.setY(game_->getWindowHeight());
				break;
			}
			Vector2D c(0, 0);
			double rx = game_->getRandGen()->nextInt(-50, 51),
				ry = game_->getRandGen()->nextInt(-50, 51);
			c.setX(game_->getWindowWidth() / 2 + rx);
			c.setY(game_->getWindowHeight() / 2 + ry);

			Vector2D vel = (c - p).normalize() * (game_->getRandGen()->nextInt(0, 11))/10;

			//cout << vel << endl << c << endl << p << endl << endl;
			a->pos_ = p;
			a->vel = vel;
			a->rotation = game_->getRandGen()->nextInt(0, 361);
			a->gen = game_->getRandGen()->nextInt(1, 4);
			a->height_ = a->width_ = 10 + 3 * a->gen;
			a->inUse = true;
		}	

	}
}

AsteroidPool::AsteroidPool() :
	Component(ecs::AsteroidPool),
	pool([](Asteroid* o) {return o->inUse; })
{}
	
AsteroidPool::~AsteroidPool() {
}
//inicializamos del pool
void AsteroidPool::init() {
	//generateAsteroids(10);
}


//desactivamos todos los asteroides del pool
void AsteroidPool::disableAll() {
	for (auto& a : pool.getPool()) {
		a->inUse = false;
	}
}

//Desactiva la bala y activa dos asteroides con vel  diferente y pos parecida al asteroide padre
//bajamos uno a su generacion (si es 0 no crea)
void AsteroidPool::onCollision(Asteroid* a, Bullet* b) {
	//b->inUse = false;
	a->inUse = false;
	if (a->gen > 0) {
		
		Vector2D v = a->vel.rotate(a->gen * 45);
		Vector2D pos = a->pos_ + v.normalize();
		Asteroid* a1 = pool.getObj(),
			* a2 = pool.getObj();
		a1->pos_ = pos;
		a1->vel = v;
		a1->gen = a->gen - 1;

		a2->pos_ = pos;
		a2->vel = v * -1;
		a2->gen = a->gen - 1;

	}
}

size_t AsteroidPool::getNumOfAsteroid() {
	int numAsteroid = 0;
	for (auto& a : pool.getPool()) {
		if (a->inUse) numAsteroid++;
	}
	return numAsteroid;
}

 std::vector<AsteroidPool::Asteroid*> AsteroidPool::getPool(){
	 return pool.getPool();
}
