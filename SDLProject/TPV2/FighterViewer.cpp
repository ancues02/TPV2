#include "FighterViewer.h"

#include  "Entity.h"
#include "SDL_macros.h"

FighterViewer::FighterViewer() :
	Component(ecs::FighterViewer),
	tr_(nullptr),
	texture(nullptr)
{}

FighterViewer::~FighterViewer(){}

void FighterViewer::init() {
	tr_ = GETCMP1_(Transform);
	texture = game_->getTextureMngr()->getTexture(Resources::Airplanes);
}

void FighterViewer::draw() {
	//SDL_Renderer* renderer = game_->getRenderer();
	//Transform* c = tr_;

	// the rotation angle of the object wrt to
	//double angle = c->getRot();
	SDL_Rect rect;
	rect = RECT(tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(), tr_->getH());

	texture->render(rect,tr_->getRot(), { 47, 90, 207, 250 });

}