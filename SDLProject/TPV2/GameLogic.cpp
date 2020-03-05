#include "GameLogic.h"
#include "Collisions.h"
#include "Resources.h"
#include "Entity.h"
GameLogic::GameLogic(Transform* fighterTR_, AsteroidPool* ast_pool, BulletsPool* bullet_pool, Health* fighterH_) :
		Component(ecs::GameLogic), //
	fighterTR_(fighterTR_), //
	ast_pool(ast_pool), //
	bullet_pool(bullet_pool), //
	fighterH_(fighterH_),
		scoreManager_(nullptr) //
{
}

GameLogic::~GameLogic() {
}

void GameLogic::init() {
	// scoreManager_ = GETCMP2(ecs::ScoreManager,ScoreManager);
	scoreManager_ = GETCMP1_(ScoreManager);
}

void GameLogic::update() {
	//vector<Asteroid*
	switch (scoreManager_->getState()) {
	case Running://comprobamos colisiones
		for (int i = 0; i < ast_pool->getPool().size(); i++) {//comprobamos colision entre asteroide y fighter
			Asteroid* as = ast_pool->getPool().at(i);
			if (as->inUse) {
				if (Collisions::collides(fighterTR_->getPos(), fighterTR_->getW(),
					fighterTR_->getH(), as->pos_, as->width_, as->height_))
				{
					ast_pool->disableAll();
					bullet_pool->disableAll();
					fighterH_->decrease_health();
					
					if (fighterH_->getHealth() <= 0)
						scoreManager_->setState(Lose);
					else scoreManager_->setState(Stop);
				}

				else {//comprobacion de colisiones de balas con asteroides
					for (int j = 0; j < bullet_pool->getPool().size(); j++) {
						Bullet* bullet = bullet_pool->getPool().at(j);
						if (bullet->inUse &&
							Collisions::collides(bullet->pos_, bullet->width_,
								bullet->height_, as->pos_, as->width_, as->height_)) {

							bullet_pool->onCollision(bullet, as);
							ast_pool->onCollision(as, bullet);

							scoreManager_->addScore(1);
							if (ast_pool->getNumOfAsteroid() == 0) {
								scoreManager_->setState(Win);
							}
						}
					}

				}
			}

		}
		break;
	case Stop:
		fighterTR_->setVel(0, 0);
		fighterTR_->setPos(game_->getWindowWidth() / 2, game_->getWindowHeight() / 2);
		bullet_pool->disableAll();
		break;
	
	case Lose:
		fighterTR_->setVel(0, 0);
		fighterTR_->setPos(game_->getWindowWidth() / 2, game_->getWindowHeight() / 2);
		bullet_pool->disableAll();
		fighterH_->reset_health();
		scoreManager_->resetScore();
		break;
	case Win:
		fighterTR_->setVel(0, 0);
		fighterTR_->setPos(game_->getWindowWidth() / 2, game_->getWindowHeight() / 2);
		bullet_pool->disableAll();
		fighterH_->reset_health();
		scoreManager_->resetScore();
		break;
	}
	

}

