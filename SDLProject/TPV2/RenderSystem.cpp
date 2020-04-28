#include "RenderSystem.h"

//renderizamos la entidad e 
void RenderSystem::draw(Entity* e)
{
	Transform* tr = e->getComponent<Transform>(ecs::Transform);
	ImageComponent* img = e->getComponent<ImageComponent>(ecs::ImageComponent);
	SDL_Rect dest =
		RECT(tr->position_.getX(), tr->position_.getY(), tr->width_,
			tr->height_);
	img->tex_->render(dest, tr->rotation_);
}
//renderizamos el score
void RenderSystem::drawScore()
{
	auto sc =
		mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<Score>(ecs::Score);
	Texture scoreMsg(game_->getRenderer(), std::to_string(sc->points_),
		game_->getFontMngr()->getFont(Resources::ARIAL24),
		{ COLOR(0x0000ffff) });
	scoreMsg.render(game_->getWindowWidth() / 2 - scoreMsg.getWidth() / 2,
		10);
}

//renderizamos el fighter
void RenderSystem::drawFighter(Entity* e)
{

	Transform* tr = e->getComponent<Transform>(ecs::Transform);
	ImageComponent* img = e->getComponent<ImageComponent>(ecs::ImageComponent);
	SDL_Rect dest =
		RECT(tr->position_.getX(), tr->position_.getY(), tr->width_,
			tr->height_);
	img->tex_->render(dest, tr->rotation_, { 47, 90, 207, 250 });
}

//Colocamos las vidas en la esquina superior izquierda
void RenderSystem::drawHealth()
{
	auto healthCp =
		mngr_->getHandler(ecs::_hdlr_Fighter)->getComponent<Health>(ecs::Health);
	Texture* heart = game_->getTextureMngr()->getTexture(Resources::Heart);
	SDL_Rect rect{ 0, 0,heart->getWidth(), heart->getHeight() };
	for (int i = healthCp->health_; i > 0; i--) {
		heart->render(rect);
		rect.x += heart->getWidth();
	}
}

//llamamos a los diferentes render si estamos en running
//sino vemos en que estado estamos para mostrar un mensaje u otro
void RenderSystem::update()
{
	auto state = mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<GameState>(ecs::GameState);

	if (state->currentState == state->Running) {
		// draw asteroids
		for (auto& e : mngr_->getGroupEntities(ecs::_grp_Asteroid)) {
			draw(e);
		}
		//draw bullets
		for (auto& e : mngr_->getGroupEntities(ecs::_grp_Bullet)) {
			draw(e);
		}
	}
	else {
		if (state->currentState == state->Win) {
			// info message
			Texture msg(game_->getRenderer(), "YOU WIN", game_->getFontMngr()->getFont(Resources::ARIAL24), { COLOR(0x00ffffff) });
			msg.render(game_->getWindowWidth() / 2 - msg.getWidth() / 2, game_->getWindowHeight() - msg.getHeight() - 150);
		}
		else if (state->currentState == state->Lose) {
			// info message
			Texture msg(game_->getRenderer(), "YOU LOSE", game_->getFontMngr()->getFont(Resources::ARIAL24), { COLOR(0xff00ffff) });
			msg.render(game_->getWindowWidth() / 2 - msg.getWidth() / 2, game_->getWindowHeight() - msg.getHeight() - 150);
		}

		// info message
		Texture msg(game_->getRenderer(), "Press ANY KEY to start game", game_->getFontMngr()->getFont(Resources::ARIAL24), { COLOR(0xff0000ff) });
		msg.render(game_->getWindowWidth() / 2 - msg.getWidth() / 2, game_->getWindowHeight() - msg.getHeight() - 10);
	}
	// draw fighter
	drawFighter(mngr_->getHandler(ecs::_hdlr_Fighter));

	// draw score
	drawScore();
	//draw health
	drawHealth();
}
