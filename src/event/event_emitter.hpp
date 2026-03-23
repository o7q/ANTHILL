#pragma once

#include <memory>
#include <vector>

template <typename T> class EventEmitter
{
  public:
    void emit(std::unique_ptr<T> event)
    {
        m_events.push_back(std::move(event));
    }

    const std::vector<std::unique_ptr<T>> &getEmittedEvents() const
    {
        return m_events;
    }

    void purge() { m_events.clear(); }

  private:
    std::vector<std::unique_ptr<T>> m_events;
};
