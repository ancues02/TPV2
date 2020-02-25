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
void AsteroidsViewer::draw() {
	for (auto& a : pool->getPool()) {
		SDL_Rect rect;
		rect = RECT(a->pos_.getX(), a->pos_.getY(),a->width_, a->height_);

		texture->render(rect,a->rotation, { 47, 90, 207, 250 });
	}
}