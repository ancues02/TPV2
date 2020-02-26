#include "SDL_macros.h"
#include "Asteroids.h"
#include <assert.h>

#include "GameCtrl.h"
#include "GameLogic.h"
#include "InputHandler.h"
#include "FighterCtrl.h"
#include "VelocityVectorViewer.h"
#include "PaddleMouseCtrl.h"
#include "FighterMotion.h"
#include "Rectangle.h"
#include "ScoreManager.h"
#include "ScoreViewer.h"
#include "SimpleMoveBahviour.h"
#include "Transform.h"
#include "SDLGame.h"

#include "FighterViewer.h"
#include "Health.h"
#include "Gun.h"
#include "SDL_macros.h"
#include "AsteroidPool.h"
#include "AsteroidsMotion.h"
#include "AsteroidsViewer.h"
#include "BulletsPool.h"

using namespace std;

Asteroids::Asteroids() :
		game_(nullptr), //
		entityManager_(nullptr), //
		exit_(false) {
	initGame();
}

Asteroids::~Asteroids() {
	closeGame();
}

void Asteroids::initGame() {
	

	game_ = SDLGame::init("Asteroids", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);

	entityManager_ = new EntityManager(game_);

	Entity *Fighter = entityManager_->addEntity();
	Transform * FighterTr = Fighter->addComponent<Transform>();
	Fighter->addComponent<FighterCtrl>();
	Fighter->addComponent<FighterMotion>();
	//leftPaddle->addComponent<Rectangle,SDL_Color>({COLOR(0xAA0000FF)});
	FighterTr->setPos(5, game_->getWindowHeight() / 2 - 25);
	FighterTr->setWH(100, 100);
	//leftPaddle->addComponent<VelocityVectorViewer>();
	Fighter->addComponent<FighterViewer>();
	Fighter->addComponent<Health>();
	Fighter->addComponent<Gun>();

	
	/*Fighter->addComponent<AsteroidPool>();
	Fighter->getComponent<AsteroidPool>(ecs::CmpIdType(ecs::AsteroidPool))->generateAsteroids(10);*/
	
	Entity* AsteroidPool_ = entityManager_->addEntity();
	AsteroidPool_->addComponent<AsteroidPool>();
	AsteroidPool_->addComponent<AsteroidsMotion>();
	AsteroidPool_->addComponent<AsteroidsViewer>();


	Entity *gameManager = entityManager_->addEntity();
	gameManager->addComponent<ScoreManager>(5);
	//gameManager->addComponent<GameLogic>(ballTR, leftPaddleTR, rightPaddleTR);
	gameManager->addComponent<ScoreViewer>();
	//gameManager->addComponent<GameCtrl>(GETCMP2(ball, Transform));

	
}

void Asteroids::closeGame() {
	delete entityManager_;
}

void Asteroids::start() {
	exit_ = false;

	while (!exit_) {
		Uint32 startTime = game_->getTime();

		handleInput();
		update();
		render();

		Uint32 frameTime = game_->getTime() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}

void Asteroids::stop() {
	exit_ = true;
}

void Asteroids::handleInput() {

	InputHandler *ih = InputHandler::instance();

	ih->update();

	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(SDLK_ESCAPE)) {
			exit_ = true;
		}

		if (ih->isKeyDown(SDLK_f)) {
			int flags = SDL_GetWindowFlags(game_->getWindow());
			if (flags & SDL_WINDOW_FULLSCREEN) {
				SDL_SetWindowFullscreen(game_->getWindow(), 0);
			} else {
				SDL_SetWindowFullscreen(game_->getWindow(),
						SDL_WINDOW_FULLSCREEN);
				
			}
		}
	}

}

void Asteroids::update() {
	entityManager_->update();
}

void Asteroids::render() {
	SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x00AAAAFF));
	SDL_RenderClear(game_->getRenderer());

	entityManager_->draw();

	SDL_RenderPresent(game_->getRenderer());
}

