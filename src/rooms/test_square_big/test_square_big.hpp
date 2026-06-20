#pragma once

#include "room/room.hpp"

class TestSquareBigRoom : public Room
{
  public:
    TestSquareBigRoom();

    void writeToLayer(px::Vec2i worldTopLeft,
                      px::ChunkMap<StructurePositionalSpawnData> &dataOut) const override;
};
