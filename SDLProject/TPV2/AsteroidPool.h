#pragma once
#include "Component.h"
#include "ObjectPool.h"
#include "Asteroid.h"
#include "SRandBasedGenerator.h"
class AsteroidPool : public Component
{
public:
	AsteroidPool();
	virtual ~AsteroidPool();

	/*inline void setCtrlKeys(SDL_Keycode left, SDL_Keycode right,
			SDL_Keycode mov) {
		rotateLeft = left;
		rotateRight = right;
		move = mov;
	}*/

	void init() override;
	void update() override;
	void generateAsteroids(int n);
private:
	ObjectPool<Asteroid,30> pool;
};

