#pragma once
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include "Vector2D.h"

namespace msg {

using msgSizeType = uint32_t;

enum MsgId : uint8_t {
	_CONNECTED, //
	_CONNECTION_REFUSED, //
	_CLIENT_DISCONNECTED, //
	_PLAYER_INFO, //
	_FIGHTER_INFO, //
	_BULLET_INFO, //
	_START_GAME, //
	_START_REQ, //
	//
	_last_MsgId_
};

#pragma pack(push,1)

struct Message {
	Message(msgSizeType size, MsgId id) :
			size(size), senderClientId(0), id(id) {
	}
	Message(MsgId id) :
			Message(sizeof(Message), id) {
	}
	msgSizeType size;
	uint32_t senderClientId;
	MsgId id;
};

struct ConnectedMsg: Message {
	ConnectedMsg(int clientId) :
			Message(sizeof(ConnectedMsg), _CONNECTED), clientId(clientId) {
	}
	uint32_t clientId;
};

struct ClientDisconnectedMsg: Message {
	ClientDisconnectedMsg(uint32_t clientId) :
			Message(sizeof(ClientDisconnectedMsg), _CLIENT_DISCONNECTED), clientId(
					clientId) {
	}
	uint32_t clientId;
};

struct FighterInfoMsg : Message {
	FighterInfoMsg(const Vector2D& pos, double rot) :
		Message(sizeof(FighterInfoMsg), _FIGHTER_INFO), pos(pos), rot(rot) {
	}
	Vector2D pos;
	double rot;
};

struct BulletInfoMsg : Message {
	BulletInfoMsg(const Vector2D& pos, const Vector2D& vel, double w, double h) :
		Message(sizeof(BulletInfoMsg), _BULLET_INFO), pos(pos), vel(vel), w(w), h(h) {
	}
	Vector2D pos;
	Vector2D vel;
	double w;
	double h;
}; 

#pragma pack(pop)

}
