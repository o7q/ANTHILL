#pragma once

#include "room/room.hpp"

class TestLongRoom : public Room
{
  public:
    TestLongRoom();

    void writeToLayer(px::Vec2i worldTopLeft,
                      px::ChunkMap<StructurePositionalSpawnData> &dataOut) const override;
};
