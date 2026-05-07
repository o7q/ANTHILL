#pragma once

#include <memory>
#include <vector>

template <typename EventType> class EventPool
{
  public:
    void emit(std::unique_ptr<EventType> event) { m_events.push_back(std::move(event)); }
    const std::vector<std::unique_ptr<EventType>> &getEvents() const { return m_events; }
    void flush() { m_events.clear(); }

  private:
    std::vector<std::unique_ptr<EventType>> m_events;
};
