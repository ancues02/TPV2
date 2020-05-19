#include "NetworkingSystem.h"

#include "messages.h"
#include "Manager.h"

NetworkingSystem::NetworkingSystem() :
		System(ecs::_sys_NetWorking) {

}

NetworkingSystem::~NetworkingSystem() {
}

void NetworkingSystem::recieve(const msg::Message &msg) {
	if (msg.senderClientId == mngr_->getClientId()) {
		game_->getNetworking()->send(msg);
	}
}

void NetworkingSystem::update() {
	auto net = game_->getNetworking();
	msg::Message *msg = nullptr;

	while ((msg = net->recieve()) != nullptr) {
		switch (msg->id) {
		case msg::_CLIENT_DISCONNECTED:
			mngr_->forwardMsg<msg::ClientDisconnectedMsg>(msg->senderClientId,
					static_cast<msg::ClientDisconnectedMsg*>(msg)->clientId);
			break;
		case msg::_PLAYER_INFO:
			mngr_->forwardMsg<msg::Message>(msg->senderClientId, msg::_PLAYER_INFO);
			break;
		case msg::_FIGHTER_INFO: {
			msg::FighterInfoMsg* fMsg = static_cast<msg::FighterInfoMsg*>(msg);
			mngr_->forwardMsg<msg::FighterInfoMsg>(msg->senderClientId,
				fMsg->pos, fMsg->rot);
			break;
		}
		case msg::_BULLET_INFO: {
			msg::BulletInfoMsg* bMsg = static_cast<msg::BulletInfoMsg*>(msg);
			mngr_->forwardMsg<msg::BulletInfoMsg>(msg->senderClientId,
				bMsg->pos, bMsg->vel, bMsg->w, bMsg->h);
			break;
		}
		case msg::_START_REQ: {
			mngr_->forwardMsg<msg::Message>(msg->senderClientId, msg::_START_REQ);
			break;
		}
		case msg::_START_GAME: {
			mngr_->forwardMsg<msg::Message>(msg->senderClientId, msg::_START_GAME);
			break;
		}
		case msg::_BULLET_FIGHTER_COLLISION: {
			mngr_->forwardMsg<msg::BulletFighterCollisionMsg>(msg->senderClientId,
				static_cast<msg::BulletFighterCollisionMsg*>(msg)->fighter_id);
			break;
		}
		default:
			assert(false);
			break;
		}
	}

}
