#pragma once

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_stdinc.h>
#include <vector>

class EventHandler
{
  public:
    enum class EventType
    {
        WINDOW_QUIT
    };

  public:
    EventHandler() = default;
    EventHandler(const EventHandler &other) = delete;
    EventHandler &operator=(const EventHandler &other) = delete;

    void resetEvents();
    void poll(SDL_Event &event);
    bool didEventOccur(EventType eventType) const;

  private:
    std::vector<EventType> m_triggeredEvents;
};
