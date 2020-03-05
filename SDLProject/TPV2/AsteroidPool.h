#pragma once
#include "Component.h"
#include "ObjectPool.h"

class Bullet;
struct Asteroid {
public:
	Vector2D pos_, vel;
	int rotation;
	int width_;
	int height_;
	int gen;
	bool inUse = false;
};
class AsteroidPool : public Component
{
public:
	
	AsteroidPool();
	virtual ~AsteroidPool();

	

	void init() override;
	//void update() override;
	void generateAsteroids(int n);
	void disableAll();
	void onCollision(Asteroid* a, Bullet* b);
	size_t getNumOfAsteroid();
	std::vector<Asteroid*> getPool();
private:

	ObjectPool<Asteroid,30> pool;
};

