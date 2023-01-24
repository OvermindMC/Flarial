#pragma once
#include "../../Utils/Utils.h"
#include "../../Mem/Mem.h"

enum class TextPacketType { RAW = 0, CHAT = 1, TRANSLATION = 2, POPUP = 3, JUKEBOX_POPUP = 4, TIP = 5, SYSTEM = 6, WHISPER = 7, ANNOUNCEMENT = 8, JSON_WHISPER = 9, JSON = 10, JSON_ANNOUNCEMENT = 11 };

enum InputMode { INPUT_MODE_UNKNOWN = 0, MOUSE = 1, TOUCH = 2, GAME_PAD = 3, MOTION_CONTROLLER = 4 };
enum PlayMode { PLAY_MODE_NORMAL = 0, TEASER = 1, SCREEN = 2, VIEWER = 3, REALITY = 4, PLACEMENT = 5, LIVING_ROOM = 6, EXIT_LEVEL = 7, EXIT_LEVEL_LIVING_ROOM = 8, NUM_MODES = 9 };

enum MovePacketMode { MOVE_PACKET_MODE_NORMAL = 0, RESET = 1, TELEPORT = 2, ROTATION = 3 };
enum MovePacketCause { MOVE_PACKET_CAUSE_UNKNOWN = 0, PROJECTILE = 1, CHORUS_FRUIT = 2, COMMAND = 3, BEHAVIOR = 4 };

class Packet {
public:
    uintptr_t** VTable;
private:
    char pad[0x24];
public:
    template<typename P>
    auto setVTable(uintptr_t sig) -> void;
public:
    auto getName(void) -> std::string;
};

class TextPacket : public Packet {
public:
    TextPacket(void);
    TextPacket(std::string, std::string);
public:
    TextPacketType type;
public:
    std::string author;
    std::string message;
private:
    unsigned char paddd[24];
public:
    bool translationNeeded = false;
private:
    unsigned char padddd[7];
public:
    std::string xboxUserId;
    std::string platformChatId;
};

class PlayerAuthInputPacket : public Packet {
public:
    PlayerAuthInputPacket(void);
    PlayerAuthInputPacket(Vec3<float>, Vec2<float>, float, Vec3<float>);
public:
    Vec2<float> bodyRot;
    Vec3<float> position;
public:
    float headYaw;
    Vec3<float> velocity;
private:
    char pad[0x1C];
public:
    InputMode inputMode;
private:
    char padd[0x3];
public:
    PlayMode playMode;
};

class MovePlayerPacket : public Packet {
public:
    MovePlayerPacket(void);
    MovePlayerPacket(class Actor*, Vec3<float>, Vec2<float>, float, bool);
public:
    uint64_t runtimeId;
    Vec3<float> position;
public:
    Vec2<float> bodyRot;
    float headYaw;
public:
    MovePacketMode mode;
    bool onGround;
private:
    char pad[0x6];
public:
    uint64_t ridingRuntimeId;
    MovePacketCause teleportCause;
};

class NetworkStackLatencyPacket : public Packet {
public:
    NetworkStackLatencyPacket(void);
};

class PlayerHotbarPacket : public Packet {
public:
    PlayerHotbarPacket(void);
    PlayerHotbarPacket(uint64_t, class ItemStack*, int);
private:
    char padd[0x110];
public:
    BUILD_ACCESS(this, uint64_t, runtimeId, 0x30);
    BUILD_ACCESS(this, uintptr_t*, idk1, 0x40);
    BUILD_ACCESS(this, uint8_t, heldStackCount, 0x48);
    BUILD_ACCESS(this, int, idk2, 0x58);
    BUILD_ACCESS(this, uintptr_t*, itemStack, 0x80);
    BUILD_ACCESS(this, int, windowId, 0x88);
    BUILD_ACCESS(this, int, slot1, 0x98);
    BUILD_ACCESS(this, int, slot2, 0x9C);
    BUILD_ACCESS(this, int, slot257, 0xA1);
    BUILD_ACCESS(this, int, slot3, 0xA2);
};

class PlayerActionPacket : public Packet {
public:
    PlayerActionPacket(void);
private:
    char padd[0x110];
public:
    BUILD_ACCESS(this, Vec3<int>, blockPos, 0x30);
    BUILD_ACCESS(this, char, blockFace, 0x48);
    BUILD_ACCESS(this, int, action, 0x4C);
public:
    BUILD_ACCESS(this, uint64_t, runtimeId, 0x50);
};

enum TransactionType {
    Normal = 0, Inventory_Mismatch = 1, Item_Use = 2, Item_Use_On_Entity = 3, Item_Release = 4
};

class InventoryTransaction {
private:
    char padd[0x110];
public:
    BUILD_ACCESS(this, TransactionType, type, 0x8);
};

class TransactionUseItem : public InventoryTransaction {
public:
    BUILD_ACCESS(this, uint64_t, targetEntityRuntimeId, 0x68);
public:
    BUILD_ACCESS(this, int, actionType, 0x70); /* Interact = 0, Attack = 1 */
    BUILD_ACCESS(this, int, hotbarSlot, 0x74);
    BUILD_ACCESS(this, Vec3<float>, playerPos, 0xD8);
};

class InventoryTransactionPacket : public Packet {
public:
    InventoryTransactionPacket(void);
private:
    char padd[0x110];
public:
    BUILD_ACCESS(this, InventoryTransaction*, transaction, 0x58);
};