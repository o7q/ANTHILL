#include "rooms.hpp"
#include "identifiers/rooms.hpp"
#include "rooms/test_room.hpp"
#include <memory>

void initRooms(AssetPool<RoomID, Room> &assets)
{
    std::unordered_map<RoomID, std::unique_ptr<Room>> v;

    v[RoomID::Test] = std::make_unique<TestRoom>();

    for (auto &[id, data] : v)
    {
        assets.add(id, std::move(data));
    }
}
