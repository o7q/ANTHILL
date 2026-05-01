#pragma once

#include <memory>
#include <vector>

template <typename T> class EventPool
{
  public:
    void emit(std::unique_ptr<T> event) { m_events.push_back(std::move(event)); }
    const std::vector<std::unique_ptr<T>> &getEvents() const { return m_events; }
    void clear() { m_events.clear(); }

  private:
    std::vector<std::unique_ptr<T>> m_events;
};
