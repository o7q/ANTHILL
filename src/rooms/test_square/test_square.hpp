#pragma once

#include "room/room.hpp"

class TestSquareRoom : public Room
{
  public:
    TestSquareRoom();

    void writeToLayer(px::Vec2i worldTopLeft,
                      px::ChunkMap<StructurePositionalSpawnData> &dataOut) const override;
};
