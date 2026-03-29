#pragma once

#include <vector>

template <typename T> class EventEmitter
{
  public:
    void emit(T event) { m_events.push_back(std::move(event)); }
    void purge() { m_events.clear(); }

    const std::vector<T> &getEmittedEvents() const { return m_events; }

  private:
    std::vector<T> m_events;
};

template<class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };

template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;
