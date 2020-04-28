#include "AsteroidSystem.h"
#include "GameCtrlSystem.h"


//se llama cuando hay colision entre un asteroide y una bala. 
//desactiva el asteroide y lo divide en dos si su generacion es mayor que 0
//los dos nuevos tienen una generacion menos y se les cambia su velocidad, rotacion, tam
//si ya no quedan asteroides se avisa al gameCtrlSystem
void AsteroidSystem::onCollisionWithBullet(Entity* a, Entity* b)
{
	a->setActive(false);
	AsteroidLifeTime* aLT = a->getComponent<AsteroidLifeTime>(ecs::AsteroidLifeTime);
	game_->getAudioMngr()->playChannel(Resources::Explosion, 0, 1);
	if (aLT->gen_ > 0) {
		Transform* aTR = a->getComponent<Transform>(ecs::Transform);
		Vector2D vel = aTR->velocity_.rotate((double)aLT->gen_ * 45);
		int newGen = aLT->gen_ - 1;
		Vector2D pos = aTR->position_ + vel.normalize();
		Vector2D pos2 = aTR->position_ - vel.normalize();
		double rotation = game_->getRandGen()->nextInt(0, 361);
		double rotation2 = game_->getRandGen()->nextInt(0, 361);
		double width = 10 + 3 * newGen;
		double height = width;

		Entity* a1 = mngr_->addEntity<AsteroidPool>(pos, vel, width, height, rotation, newGen);
		if (a1 != nullptr)
			a1->addToGroup(ecs::_grp_Asteroid);
		Entity* a2 = mngr_->addEntity<AsteroidPool>(pos2, (vel * -1), width, height, rotation2, newGen);
		if (a2 != nullptr)
			a2->addToGroup(ecs::_grp_Asteroid);
		numOfAsteroids_ += 1;//se divide en dos pero se quita el actual
	}
	else {

		if (--numOfAsteroids_ <= 0) {
			mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->onAsteroidsExtenction();
		}
	}
}

//se a�aden n asteroides con posicion, velocidad ... diferentes pero yendo hacia el centro de la pantalla
void AsteroidSystem::addAsteroids(int n)
{
	numOfAsteroids_ = n;
	for (auto i = 0; i < n; i++) {
		Vector2D p(0, 0);
		switch (game_->getRandGen()->nextInt(0, 4)) {
		case 0://left
			p.setY(game_->getRandGen()->nextInt(1, game_->getWindowHeight()));

			break;
		case 1://up
			p.setX(game_->getRandGen()->nextInt(1, game_->getWindowWidth()));

			break;
		case 2://Right
			p.setY(game_->getRandGen()->nextInt(1, game_->getWindowHeight()));
			p.setX(game_->getWindowWidth());

			break;
		case 3://bottom
			p.setX(game_->getRandGen()->nextInt(1, game_->getWindowWidth()));
			p.setY(game_->getWindowHeight());
			break;
		}
		Vector2D c(0, 0);
		double rx = game_->getRandGen()->nextInt(-50, 51),
			ry = game_->getRandGen()->nextInt(-50, 51);
		c.setX(game_->getWindowWidth() / 2 + rx);
		c.setY(game_->getWindowHeight() / 2 + ry);

		Vector2D vel = (c - p).normalize() * (game_->getRandGen()->nextInt(1, 11)) / 10;
		int gen = game_->getRandGen()->nextInt(1, 3);
		double w = 10 + 3 * gen;
		double h = w;
		double rotation = game_->getRandGen()->nextInt(0, 361);

		//se a�aden las entidades
		Entity* e = mngr_->addEntity<AsteroidPool>(p, vel, w, h, rotation, gen);
		if (e != nullptr)
			e->addToGroup(ecs::_grp_Asteroid);
	}
}
//se actualizan los asteroides que estan activos
void AsteroidSystem::update()
{
	for (auto& e : mngr_->getGroupEntities(ecs::_grp_Asteroid)) {

		if (!e->isActive())
			return;

		Transform* tr = e->getComponent<Transform>(ecs::Transform);
		if (tr->position_.getX() > game_->getWindowWidth())
			tr->position_.setX(-tr->width_);
		else if (tr->position_.getX() + tr->width_ < 0)
			tr->position_.setX(game_->getWindowWidth());
		if (tr->position_.getY() > game_->getWindowHeight())
			tr->position_.setY(-tr->height_);
		else if (tr->position_.getY() + tr->height_ < 0)
			tr->position_.setY(game_->getWindowHeight());
		tr->rotation_ += 1;

		tr->position_ = tr->position_ + tr->velocity_;
	}
}
