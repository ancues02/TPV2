#include "AudioSystem.h"

#include "SDLGame.h"
#include "Manager.h"
#include "messages.h"

AudioSystem::AudioSystem() : System(ecs::_sys_Audio)
{
}

void AudioSystem::init() {
	game_->getAudioMngr()->playMusic(Resources::PacMan_Intro);
}

void AudioSystem::recieve(const msg::Message& msg)
{
	switch (msg.id)
	{
	case msg::_GAME_READY: {
		game_->getAudioMngr()->playMusic(Resources::PacMan_Intro);
		break;
	}
	case msg::_GAME_START: {
		game_->getAudioMngr()->haltMusic();
		break;
	}
	case msg::_GAME_OVER: {
		game_->getAudioMngr()->haltMusic();
		break;
	}
	case msg::_PACMAN_DEATH: {
		game_->getAudioMngr()->playChannel(Resources::PacMan_Death, 0);
		break;
	}
	case msg::_NO_MORE_FOOD: {
		game_->getAudioMngr()->playChannel(Resources::PacMan_Won, 0);
		break;
	}
	case msg::_PACMAN_EAT: {
		game_->getAudioMngr()->playChannel(Resources::PacMan_Eat, 0);		
		break;
	}
	default:
		break;
	}
}
