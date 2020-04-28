#include "GameCtrlSystem.h"

//iniciamos el GameCtrlSystem 
void GameCtrlSystem::init()
{
	Entity* e = mngr_->addEntity();
	auto sc = e->addComponent<Score>();
	sc->points_ = 0;
	e->addComponent<GameState>();
	mngr_->setHandler(ecs::_hdlr_GameState, e);
}

//comprobamos  en que estado estamos para mostrar unas cosas u otras en pantalla 
void GameCtrlSystem::update()
{
	auto ih = game_->getInputHandler();
	auto gh = mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<GameState>(ecs::GameState);
	if (InputHandler::instance()->keyDownEvent()) {
		// Reinicia la puntuacion si termina el juego
		if (gh->currentState == gh->Lose || gh->currentState == gh->Win) {
			auto fighter = mngr_->getHandler(ecs::_hdlr_Fighter)->getComponent<Health>(ecs::Health);
			fighter->health_ = fighter->init_Health_;
			auto score = mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<Score>(ecs::Score);
			score->points_ = 0;

		}
		if (gh->currentState != gh->Running) {
			gh->currentState = gh->Running;
			//game_->getAudioMngr()->playMusic(Resources::Imperial);
			mngr_->getSystem<AsteroidSystem>(ecs::_sys_Asteroids)->addAsteroids(10);
		}
	}
}

//desactivamos todos los asteroides y balas
//vamos a un estado u otro dependiende de las vidas del jugador
//con 0 vidas vas al estado lose, y sino al estado stop
void GameCtrlSystem::onFighterDeath()
{
	mngr_->getSystem<AsteroidSystem>(ecs::_sys_Asteroids)->disableAll();
	mngr_->getSystem<BulletsSystem>(ecs::_sys_Bullets)->disableAll();

	auto gh = mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<GameState>(ecs::GameState);
	Health* fighterHealth = mngr_->getHandler(ecs::_hdlr_Fighter)->getComponent<Health>(ecs::Health);
	if (fighterHealth->health_ <= 0) {
		//game->getAudioMngr()->playMusic(Resources::Boooo, 0);
		gh->currentState = gh->Lose;
	}
	else {
		gh->currentState = gh->Stop;
		//game_->getAudioMngr()->haltMusic();
	}

}
//
void GameCtrlSystem::onAsteroidsExtenction()
{
	mngr_->getSystem<BulletsSystem>(ecs::_sys_Bullets)->disableAll();
	mngr_->getSystem<FighterSystem>(ecs::_sys_Fighter)->resetPosition();
	auto gh = mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<GameState>(ecs::GameState);
	gh->currentState = gh->Win;
}
