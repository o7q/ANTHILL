#pragma once

#include "room/room.hpp"

class TestLongRoom : public Room
{
  public:
    TestLongRoom();

    void writeToLayer(Vec2i worldTopLeft, ChunkMap<StructurePositionalSpawnData> &dataOut) const override;
};
