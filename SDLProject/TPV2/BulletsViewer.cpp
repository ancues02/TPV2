#include "BulletsViewer.h"
#include "Entity.h"
#include "SDL_macros.h"



BulletsViewer::BulletsViewer() :
	Component(ecs::BulletsViewer), pool(nullptr), texture(nullptr) {
}

BulletsViewer::~BulletsViewer() {
}

void BulletsViewer::init() {
	pool = GETCMP1_(BulletsPool);
	texture = game_->getTextureMngr()->getTexture(Resources::Bullet);

}

//dibuja los asteroides usados
void BulletsViewer::draw() {
	for (auto& a : pool->getPool()) {
		if (a->inUse) {
			SDL_Rect rect;
			rect = RECT(a->pos_.getX(), a->pos_.getY(), a->width_, a->height_);

			texture->render(rect, a->rotation);
		}
	}
}