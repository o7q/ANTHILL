#include "rooms.hpp"
#include "identifiers/rooms.hpp"
#include "rooms/test_long/test_long.hpp"
#include "rooms/test_square/test_square.hpp"
#include "rooms/test_square_big/test_square_big.hpp"
#include "rooms/test_tall/test_tall.hpp"
#include <memory>

void initRooms(px::AssetPool<RoomID, Room> &assets)
{
    std::unordered_map<RoomID, std::unique_ptr<Room>> v;

    v[RoomID::TestSquare]    = std::make_unique<TestSquareRoom>();
    v[RoomID::TestSquareBig] = std::make_unique<TestSquareBigRoom>();
    v[RoomID::TestTall]      = std::make_unique<TestTallRoom>();
    v[RoomID::TestLong]      = std::make_unique<TestLongRoom>();

    for (auto &[id, data] : v)
    {
        assets.add(id, std::move(data));
    }
}
