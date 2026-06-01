#pragma once

#include "room/room.hpp"

class TestSquareBigRoom : public Room
{
  public:
    TestSquareBigRoom();

    void writeToLayer(Vec2i worldTopLeft, ChunkMap<StructurePositionalSpawnData> &dataOut) const override;
};
