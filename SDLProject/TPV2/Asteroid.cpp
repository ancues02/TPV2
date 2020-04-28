#include "SDL_macros.h"
#include "Asteroid.h"
#include <assert.h>

#include "ImageComponent.h"
#include "InputHandler.h"
#include "Transform.h"
#include "SDLGame.h"

#include "SDL_macros.h"



using namespace std;

Asteroid::Asteroid() :
		game_(nullptr), //
		mngr_(nullptr), //
		exit_(false) {
	initGame();
}

Asteroid::~Asteroid() {
	closeGame();
}

void Asteroid::stop() {
	exit_ = true;
}

void Asteroid::initGame() {

	game_ = SDLGame::init("Stars", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);
	game_->getAudioMngr()->setMusicVolume(30);
	game_->getAudioMngr()->setChannelVolume(10);
	AsteroidPool::init(100);
	BulletPool::init(10);

	mngr_ = new Manager(game_);
	
	renderSystem_ = mngr_->addSystem<RenderSystem>();
	asteroidSystem_ = mngr_->addSystem<AsteroidSystem>();
	fighterSystem_ = mngr_->addSystem<FighterSystem>();
	collisionSystem_ = mngr_->addSystem<CollisionSystem>();
	gameCtrlSystem_ = mngr_->addSystem<GameCtrlSystem>();
	fighterGunSystem_ = mngr_->addSystem<FigtherGunSystem>();
	bulletSystem_ = mngr_->addSystem<BulletsSystem>();
}

void Asteroid::closeGame() {
	delete mngr_;
}

void Asteroid::start() {
	exit_ = false;
	auto ih = InputHandler::instance();

	while (!exit_) {
		Uint32 startTime = game_->getTime();
		SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x00AAAAFF));
		SDL_RenderClear(game_->getRenderer());

		ih->update();
		if (ih->keyDownEvent()) {
			if (ih->isKeyDown(SDLK_ESCAPE)) {
				exit_ = true;
				break;
			}
		}

		mngr_->refresh();
		gameCtrlSystem_->update();
		
		auto gh = mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<GameState>(ecs::GameState);
		if (gh->currentState == gh->Running) {
			asteroidSystem_->update();
			fighterSystem_->update();
			fighterGunSystem_->update();
			bulletSystem_->update();
			collisionSystem_->update();
		}
		renderSystem_->update();

		SDL_RenderPresent(game_->getRenderer());

		Uint32 frameTime = game_->getTime() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}


