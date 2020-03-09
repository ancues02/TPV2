#include "Health.h"
#include  "Entity.h"
#include "SDL_macros.h"

Health::Health() :
	Component(ecs::Health),
	tr_(nullptr),
	texture(nullptr)
{}

Health::~Health() {}

void Health::init() {
	tr_ = GETCMP1_(Transform);
	texture = game_->getTextureMngr()->getTexture(Resources::Heart); 
	health = ini_health;
}

void Health::draw() {
	
	//Colocamos las vidas en la esquina superior izquierda
	SDL_Rect rect{ 0, 0,texture->getWidth(), texture->getHeight()};
	for (int i = health; i > 0; i--) {
		texture->render(rect);
		rect.x += texture->getWidth();
	}
}

void Health::decrease_health(int damage) {
	health = max(0, health - damage);
}

void Health::reset_health() {
	health = ini_health;
}

