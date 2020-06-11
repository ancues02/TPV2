#pragma once

#include "System.h"

class FoodSystem: public System {
public:
	FoodSystem();
	void init() override;
	void update() override;
	void recieve(const msg::Message& msg) override;

private:
	int numOfFoodPieces_;

	void addFood(std::size_t n);
	void onEat(Entity* e);
	void disableAll();
};

