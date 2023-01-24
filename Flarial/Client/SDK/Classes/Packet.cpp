#include "Packet.h"
#include "Player.h"
#include "ItemStack.h"

template<typename P>
auto Packet::setVTable(uintptr_t sig) -> void {

    if (sig == NULL)
        return;

    int offset = *(int*)(sig + 3);
    this->VTable = (uintptr_t**)(sig + offset + 7);

};

auto Packet::getName(void) -> std::string {

    return std::string(Utils::CallVFunc<1, const char*>(this));

};

TextPacket::TextPacket(void) {

    static uintptr_t sig = NULL;

    if (sig == NULL)
        sig = Mem::findSig("48 8D 05 ? ? ? ? 48 89 85 ? ? ? ? 48 8D 8D ? ? ? ? E8 ? ? ? ? 48 8D 8D ? ? ? ? E8 ? ? ? ? 48 8D 8D ? ? ? ? E8 ? ? ? ? 48 8D");

    this->setVTable<TextPacket>(sig);

};

TextPacket::TextPacket(std::string authorUsername, std::string chatMessage) {

    *this = TextPacket();

    this->type = TextPacketType::CHAT;
    this->translationNeeded = false;

    this->author = authorUsername;
    this->message = chatMessage;

    this->xboxUserId = std::string("");
    this->platformChatId = std::string("");

};

PlayerAuthInputPacket::PlayerAuthInputPacket(void) {

    static uintptr_t sig = NULL;

    if (sig == NULL)
        sig = Mem::findSig("48 8D 0D ? ? ? ? 0F 57 C0 0F 11 00 C7 40 ? ? ? ? ? C7 40 ? ? ? ? ? 48 8D 05 ? ? ? ? 48 89 02 33 C0 48 89 42 28 48 89 4A 10");

    this->setVTable<PlayerAuthInputPacket>(sig);

};

PlayerAuthInputPacket::PlayerAuthInputPacket(Vec3<float> pos, Vec2<float> rot, float headYaw = 0.f, Vec3<float> vel = Vec3<float>()) {

    *this = PlayerAuthInputPacket();

    this->position = pos;

    this->bodyRot = rot;
    this->headYaw = headYaw;

    this->velocity = vel;

    this->inputMode = InputMode::MOUSE;
    this->playMode = PlayMode::SCREEN;

};

MovePlayerPacket::MovePlayerPacket(void) {

    static uintptr_t sig = NULL;

    if (sig == NULL)
        sig = Mem::findSig("48 8D 05 ? ? ? ? 48 89 42 08 48 8B 47 30");

    this->setVTable<MovePlayerPacket>(sig);

};

MovePlayerPacket::MovePlayerPacket(Actor* entity, Vec3<float> pos, Vec2<float> rot, float headYaw = 0.f, bool onGround = false) {

    *this = MovePlayerPacket();

    this->runtimeId = entity->runtimeId;
    this->position = pos;

    this->bodyRot = rot;
    this->headYaw = headYaw;

    this->mode = MovePacketMode::MOVE_PACKET_MODE_NORMAL;
    this->onGround = onGround;

    this->ridingRuntimeId = NULL;
    this->teleportCause = MovePacketCause::MOVE_PACKET_CAUSE_UNKNOWN;

};

NetworkStackLatencyPacket::NetworkStackLatencyPacket(void) {

    static uintptr_t sig = NULL;

    if (sig == NULL)
        sig = Mem::findSig("48 8D 15 ? ? ? ? C7 40 ? ? ? ? ? 33 C9 C7 40 ? ? ? ? ? 48 89 48 28 48 89 48 30 89 48 38 88 48 40 48 89 48 48 48 89 48 50");

    this->setVTable<NetworkStackLatencyPacket>(sig);

};

PlayerHotbarPacket::PlayerHotbarPacket(void) {

    static uintptr_t sig = NULL;

    if (sig == NULL)
        sig = Mem::findSig("48 8D 0D ? ? ? ? 0F 57 C0 0F 11 00 C7 40 ? ? ? ? ? C7 40 ? ? ? ? ? 48 8D 05 ? ? ? ? 48 89 02 33 C0 48 89 42 28 48 89 42 40");

    this->setVTable<PlayerHotbarPacket>(sig);

};

PlayerHotbarPacket::PlayerHotbarPacket(uint64_t runtimeId, ItemStack* itemStack, int slot) {

    *this = PlayerHotbarPacket();

    this->runtimeId = runtimeId;
    this->idk1 = nullptr;
    this->idk2 = 2;

    this->windowId = 10;

    this->slot1 = slot;
    this->slot2 = slot;
    this->slot3 = slot;

    this->slot257 = (257 * slot);

    this->itemStack = (uintptr_t*)itemStack;
    this->heldStackCount = itemStack->count;

};

PlayerActionPacket::PlayerActionPacket(void) {

    static uintptr_t sig = NULL;

    if (sig == NULL)
        sig = Mem::findSig("48 8D 0D ? ? ? ? 48 89 4C 24 ? 66 0F 7F 44 24 ? 66 0F 6F 0D ? ? ? ? 66 0F 7F 4C 24 ? 48 89 44 24 ? 48 8B 8B ? ? ? ? 48 8B 01 48 8D 54 24 ? 48 8B 40 08 FF 15 ? ? ? ? 89 BB ? ? ? ? 48 8B 03 41 B0 01");

    this->setVTable<PlayerActionPacket>(sig);

};

InventoryTransactionPacket::InventoryTransactionPacket(void) {

    static uintptr_t sig = NULL;

    if (sig == NULL)
        sig = Mem::findSig("48 8D 05 ? ? ? ? 48 89 01 48 8B D9 44 89 49");

    this->setVTable<InventoryTransactionPacket>(sig);

};