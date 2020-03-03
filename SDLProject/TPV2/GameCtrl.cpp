#include "GameCtrl.h"

#include "Entity.h"
#include "InputHandler.h"



GameCtrl::GameCtrl(AsteroidPool* ast_pool1, Health* health1) :
		Component(ecs::GameCtrl), //
		ast_pool(ast_pool1),
		health(health1),
		scoreManager_(nullptr) //
{
	
}

GameCtrl::~GameCtrl() {
}

void GameCtrl::init() {
	scoreManager_ = GETCMP1_(ScoreManager);
}

void GameCtrl::update() {

	if (InputHandler::instance()->keyDownEvent()) {
		if (!scoreManager_->isRunning()) {
			RandomNumberGenerator *r = game_->getRandGen();
			scoreManager_->setState(Running);
			ast_pool->generateAsteroids(10);
			
			//ballTR_->setVel(v.normalize() * 5);

			// rest the score if the game is over
			if (scoreManager_->isGameOver()) {
				health->reset_health();
				scoreManager_->resetScore();
			}
		}
	}
}

void GameCtrl::draw() {

	if (!scoreManager_->isRunning()) {
		Texture *hitanykey = game_->getTextureMngr()->getTexture(
				Resources::PressAnyKey);
		hitanykey->render(
				game_->getWindowWidth() / 2 - hitanykey->getWidth() / 2,
				game_->getWindowHeight() - hitanykey->getHeight() - 50);
	}

	// game over message when game is over
	if (scoreManager_->isGameOver()) {
		Texture *gameOver = game_->getTextureMngr()->getTexture(
				Resources::GameOver);
		gameOver->render(game_->getWindowWidth() / 2 - gameOver->getWidth() / 2,
				game_->getWindowHeight() - gameOver->getHeight() - 150);
	}
}
