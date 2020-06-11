#pragma once
#include <ctime>

class Entity;

namespace msg {

using msgType = std::size_t;

enum MsgId : msgType {
	_GAME_START, _GAME_OVER, _GAME_READY,
	_PACMAN_GHOST_COLLISION, 
	_PACMAN_EAT, 
	_NO_MORE_FOOD,
	_PACMAN_DEATH,

	//
	_last_MsgId_
};

struct Message {
	Message(MsgId id) :
			id(id) {
	}

	MsgId id;
};

struct PacmanEatMsg : Message {
	PacmanEatMsg(Entity* e) :
		Message(_PACMAN_EAT), e_(e) {
	}

	Entity* e_;
};
struct PacmanGhostColMsg : Message {
	PacmanGhostColMsg(Entity* e) :
		Message(_PACMAN_GHOST_COLLISION), e_(e) {
	}
	Entity* e_;
};

}
