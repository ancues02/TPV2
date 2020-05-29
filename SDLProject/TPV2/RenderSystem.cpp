#include "RenderSystem.h"

#include "ecs.h"
#include "GameCtrlSystem.h"
#include "Manager.h"
#include "SDL_macros.h"
#include "SDLGame.h"

#include "Image.h"
#include "Transform.h"
#include "Texture.h"

RenderSystem::RenderSystem() :
		System(ecs::_sys_Render) {
}

void RenderSystem::update() {
	for (auto &e : mngr_->getGroupEntities(ecs::_grp_Fighters)) {
		drawImage(e); // auto cast from unique_ptr to Entity*
	}

	for (auto &e : mngr_->getGroupEntities(ecs::_grp_Bullets))
		drawImage(e); // auto cast from unique_ptr to Entity*

	drawCtrlMessages();
	drawScore();
}

void RenderSystem::drawImage(Entity *e) {
	Transform *tr = e->getComponent<Transform>(ecs::Transform);
	Texture *tex = e->getComponent<Image>(ecs::Image)->tex_;

	SDL_Rect dest =
	RECT(tr->position_.getX(), tr->position_.getY(), tr->width_,
			tr->height_);
	tex->render(dest, tr->rotation_);
}

void RenderSystem::drawCtrlMessages() {
	auto gameCtr = mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl);
	auto gameState = gameCtr->getState();

	//Name text
	Texture nameTex(game_->getRenderer(),
		mngr_->getName(),
		game_->getFontMngr()->getFont(Resources::ARIAL24),
		{ COLOR(0xff00ffff) });
	if()
	nameTex.render(game_->getWindowWidth() / 2 - nameTex.getWidth() / 2, 10);
	
	if (gameState == GameCtrlSystem::READY) {
		auto msgTex = game_->getTextureMngr()->getTexture(
			Resources::WaitingForPlayer);
		msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2,
			(game_->getWindowHeight() - msgTex->getHeight() - 10));
	}
	else if (gameState == GameCtrlSystem::ROUNDOVER) {
		auto msgTex = game_->getTextureMngr()->getTexture(
				Resources::PressEnter);
		msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2,
				(game_->getWindowHeight() - msgTex->getHeight() - 10));
	}

	else if (gameState == GameCtrlSystem::GAMEOVER) {
		auto score = gameCtr->getScore(mngr_->getClientId());	//tu puntuación

		auto msgTex = game_->getTextureMngr()->getTexture(Resources::GameOver);
		msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2,
				(game_->getWindowHeight() - msgTex->getHeight()) / 2);
		if(score < 3)
			msgTex = game_->getTextureMngr()->getTexture(
				Resources::Lose);
		else {
			auto other_score = gameCtr->getScore((mngr_->getClientId() + 1) % 2);
			if(other_score == score)
				msgTex = game_->getTextureMngr()->getTexture(
					Resources::Draw);
			else
				msgTex = game_->getTextureMngr()->getTexture(
					Resources::Win);
		}
		msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2,
			((game_->getWindowHeight() - game_->getWindowHeight()/4) - msgTex->getHeight()/2));

		msgTex = game_->getTextureMngr()->getTexture(
			Resources::PressEnter);
		msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2,
			(game_->getWindowHeight() - msgTex->getHeight() - 10));
	}

}

void RenderSystem::drawScore() {
	auto gameCtrl = mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl);

	Texture scoreTex(game_->getRenderer(),
			to_string(gameCtrl->getScore(0)) + " - "
					+ to_string(gameCtrl->getScore(1)),
			game_->getFontMngr()->getFont(Resources::ARIAL24),
			{ COLOR(0x111122ff) });
	scoreTex.render(game_->getWindowWidth() / 2 - scoreTex.getWidth() / 2, 10);
}
