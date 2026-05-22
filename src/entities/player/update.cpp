#include "player.hpp"

#include "core/math/random.hpp"
#include "core/math/rectangle.hpp"
#include "entities/player/dash/player_dash.hpp"
#include "entity/world_interaction/against.hpp"
#include "events/entity/base.hpp"
#include "events/entity/events.hpp"
#include "events/external/events.hpp"
#include <memory>

void Player::update(const EntityUpdateContext &context, EventPool<EntityEvent> &eventsOut)
{
    update_entity_interaction(context, eventsOut);

    if (r_input.getInput(InputID::Dash)->wasPressed())
    {
        if (m_dashTarget.has_value())
        {
            Vec2i pos = m_dashTarget.value().getPosition();
            m_dash.start(Math::Angle::vectorsToAngle(m_body.getPositionFloat(), pos.toFloat()));
        }
        else
        {
            m_dash.start(Math::Angle::vectorsToAngle(m_body.getPositionFloat(), m_aimPos.toFloat()));
        }

        SoundID dashSounds[3] = {SoundID::SumiDash1, SoundID::SumiDash2, SoundID::SumiDash3};

        auto dashSoundEvent             = std::make_unique<ExternalPlaySoundEvent>();
        dashSoundEvent->soundID         = dashSounds[Math::Random::unseededRandomInt(0, 3)];
        dashSoundEvent->settings.volume = 0.1f;
        dashSoundEvent->settings.pitch  = Math::Random::unseededRandomInt(180, 200) / 100.0f;
        eventsOut.emit(std::make_unique<EntityExternalEvent>(context.id, std::move(dashSoundEvent)));
    }

    if (r_input.getInput(InputID::Dash)->wasUnpressed())
    {
        m_dash.stop();
    }

    m_dash.update(context);

    if (m_dash.getState() == PlayerDash::State::Dashing)
    {
        m_body.setVelocity(m_dash.getDashVelocity());
    }
    else
    {
        update_movement_and_jump(context);
    }

    if (r_input.getInput(InputID::Shoot)->isDown())
    {
        m_gun.shoot(m_body.getPosition(), m_angle, context.id, eventsOut);
    }
    m_gun.update(context.time.dt);

    m_bodyHandler.update(context);

    m_sprite.update({m_body, m_dash, m_angle}, context.time.dt);
    m_sound.update(
        context,
        {m_body, EntityWorldInteraction::againstSolidSurface(m_body.getPosition(), m_collider,
                                                             context.particleHandler, RectangleSide::Bottom)},
        eventsOut);

    m_comboTimer.update(context.time.dt);

    if (m_comboTimer.completed())
    {
        m_comboCounter = 0;
    }

    if (m_comboCounter >= 3)
    {
        auto slowmoEvent                  = std::make_unique<ExternalChangeSpeedEvent>();
        slowmoEvent->settings.startLength = 0.0f;
        slowmoEvent->settings.holdLength  = 0.5f;
        slowmoEvent->settings.holdSpeed   = 0.3f;
        slowmoEvent->settings.endLength   = 0.5f;

        eventsOut.emit(std::make_unique<EntityExternalEvent>(context.id, std::move(slowmoEvent)));
        m_comboCounter = 0;
    }
}
