#include "AsteroidsViewer.h"
#include "Entity.h"
#include "SDL_macros.h"



AsteroidsViewer::AsteroidsViewer() :
	Component(ecs::AsteroidsViewer), pool(nullptr),texture(nullptr) {
}

AsteroidsViewer::~AsteroidsViewer() {
}

void AsteroidsViewer::init() {
	pool = GETCMP1_(AsteroidPool);
	texture = game_->getTextureMngr()->getTexture(Resources::Asteroid);

}

//dibuja las balas en uso
void AsteroidsViewer::draw() {
	for (auto& a : pool->getPool()) {
		if (a->inUse) {
			SDL_Rect rect;
			rect = RECT(a->pos_.getX(), a->pos_.getY(), a->width_, a->height_);

			texture->render(rect, a->rotation);
		}
	}
}