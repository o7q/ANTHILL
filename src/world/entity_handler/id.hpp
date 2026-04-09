#pragma once

#include <cstdint>

class EntityIDHandler
{
  public:
    uint64_t getNext() { return ++m_current; }

  private:
    uint64_t m_current = 0;
};
