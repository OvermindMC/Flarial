#pragma once
#include "../../Utils/Utils.h"
#include "../../Mem/Mem.h"

class RaknetInstance {
public:
	auto getServerStaticIp(void) -> std::string {
		if (this->serverIp.length() <= 0)
			return "";

		if ((uintptr_t*)((uintptr_t)(this) + 0x458) != nullptr)
			if (Utils::isValidDomain((char*)((uintptr_t)(this) + 0x458)))
				return std::string((const char*)((uintptr_t)(this) + 0x458));
			else if ((char**)((uintptr_t)(this) + 0x458) != nullptr)
				return std::string((*(char**)((uintptr_t)(this) + 0x458)));

		return "";
	};
public:
	BUILD_ACCESS(this, std::string, serverName, 0x530);
	BUILD_ACCESS(this, std::string, serverIp, 0x438);
public:
	AS_FIELD(std::string, serverStaticIp, getServerStaticIp);
};

class Raknet {
public:
	BUILD_ACCESS(this, RaknetInstance*, instance, 0x8);
};

class NetworkHandler {
public:
	BUILD_ACCESS(this, Raknet*, raknet, 0x50);
};

class LoopbackPacketSender {
public:
	BUILD_ACCESS(this, NetworkHandler*, networkHandler, 0x10);
private:
	virtual ~LoopbackPacketSender(void);
public:
	virtual auto send(class Packet*) -> void;
	virtual auto sendToServer(class Packet*) -> void;
	virtual auto sendToClient(class NetworkIdentifier const&, class Packet const&, enum SubClientId) -> void;
	virtual auto sendToClient(class UserEntityIdentifierComponent*, class Packet*) -> void;
	virtual auto sendToClients(class std::vector<class NetworkIdentifierWithSubId, class std::allocator<struct NetworkIdentifierWithSubId>> const&, class Packet const&) -> void;
	virtual auto sendBroadcast(class NetworkIdentifier*, enum SubClientId, class Packet*) -> void;
	virtual auto sendBroadcast(class Packet*) -> void;
	virtual auto flush(class NetworkIdentifier const&, class std::function<void(void)>&&) -> void;
};