#pragma once

#include <cstdint>

class EntityIDHandler
{
  public:
    uint64_t getNext()
    {
        uint64_t next = m_current;
        m_current++;
        return next;
    }

  private:
    uint64_t m_current = 1;
}; // namespace EntityID
