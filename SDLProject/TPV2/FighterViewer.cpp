#include "FighterViewer.h"

#include  "Entity.h"
#include "SDL_macros.h"

FighterViewer::FighterViewer() :
	Component(ecs::FighterViewer),
	tr_(nullptr)
	//texture(Resources::images_[Resources::Airplanes].fileName);
{}

FighterViewer::~FighterViewer(){}

void FighterViewer::init() {
	tr_ = GETCMP1_(Transform);
}

void FighterViewer::draw() {
	SDL_Renderer* renderer = game_->getRenderer();
	Transform* c = tr_;

	// the rotation angle of the object wrt to
	double angle = c->getRot();

}