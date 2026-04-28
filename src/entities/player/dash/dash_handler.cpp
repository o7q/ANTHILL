#include "dash_handler.hpp"

#include "math/angle.hpp"
#include "math/interpolation.hpp"
#include "world/entity_handler/events/events.hpp"
#include "world/particle_handler/events/events.hpp"
#include <algorithm>
#include <memory>

DashHandler::DashHandler()
{
    m_startTimer.setDurationInMilliseconds(80);
    m_dashTimer.setDurationInMilliseconds(500);
}

void DashHandler::start(float angle)
{
    if (m_state == State::Idle)
    {
        m_startTimer.restart();
        m_dashTimer.restart();
        m_state = State::Charging;
        m_dashAngle = Degrees(angle).radians();
    }
}

void DashHandler::stop()
{
    m_state = State::Idle;
    m_startTimer.stop();
    m_dashTimer.stop();
}

void DashHandler::update(EntityBody &body, EventPool<EntityEvent> &eventsOut,
                         const EntityUpdateContext &context)
{
    switch (m_state)
    {
    case State::Charging:
    {
        body.setVelocity({0, 0});
        m_startTimer.update(context.dt);

        if (m_startTimer.completed())
        {
            m_state = State::Dashing;
        }
    }
    break;
    case State::Dashing:
    {
        Vec2f dir = {std::cosf(m_dashAngle), std::sinf(m_dashAngle)};

        Vec2f startVel = dir * 10.0f;
        Vec2f endVel = dir * 1.0f;

        float velX = Math::Interpolation::easeOutCubic(
            startVel.x, endVel.x,
            std::clamp(m_dashTimer.getProgress(), 0.0f, 1.0f));
        float velY = Math::Interpolation::easeOutCubic(
            startVel.y, endVel.y,
            std::clamp(m_dashTimer.getProgress(), 0.0f, 1.0f));

        body.setVelocity({velX, velY});

        auto event = std::make_unique<ParticleDrawEvent>();
        event->particle = Particle();
        event->radius = 18;
        event->position = body.getPosition() + Vec2i(velX, velY);

        auto entityEvent =
            std::make_unique<EntityParticleEvent>(context.id, std::move(event));

        eventsOut.emit(std::move(entityEvent));

        m_dashTimer.update(context.dt);

        if (m_dashTimer.completed())
        {
            m_state = State::Drained;
        }
    }
    break;
    default:
        break;
    }
}
