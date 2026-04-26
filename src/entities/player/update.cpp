#include "entities/player/player_sprite.hpp"
#include "entity/world_interaction/against.hpp"
#include "events/backend/events.hpp"
#include "item/context.hpp"
#include "item/reloadable.hpp"
#include "math/random.hpp"
#include "math/rectangle.hpp"
#include "player.hpp"
#include "world/entity_handler/events/events.hpp"
#include <memory>

void Player::update(const EntityUpdateContext &context,
                    EventPool<EntityEvent> &eventsOut)
{
    if (r_input.getInput(InputID::Left)->isDown())
    {
        m_body.setVelocityTargetX(-3.0f);
    }
    if (r_input.getInput(InputID::Right)->isDown())
    {
        m_body.setVelocityTargetX(3.0f);
    }
    if (r_input.getInput(InputID::Jump)->wasPressed())
    {
        m_jumpHandler.requestJump();
    }
    if (!r_input.getInput(InputID::Jump)->isDown())
    {
        m_jumpHandler.cancelJump();
    }

    bool onGround = EntityWorldInteraction::againstSolidSurface(
        m_body.getPosition(), m_boundingBox, context.particleHandler,
        RectangleSide::Bottom);

    m_jumpHandler.update(context.dt, onGround);

    if (m_jumpHandler.canJump())
    {
        m_body.setVelocityY(-m_jumpHandler.getJumpPower());
    }

    Item *current = m_inventory.getSelectedItem();
    if (r_input.getInput(InputID::Action1)->isDown())
    {
        if (current)
        {
            ItemUseContext itemContext;
            itemContext.ownerID = context.id;
            itemContext.heldPosition = m_body.getPosition();
            itemContext.heldAngle = m_angle;

            bool used = current->use(itemContext, eventsOut);

            if (used)
            {
                auto shootSoundEvent =
                    std::make_unique<BackendPlaySoundEvent>();

                shootSoundEvent->soundID = current->getUseSound();
                shootSoundEvent->settings.volume = 0.2f;
                shootSoundEvent->settings.pitch =
                    100.0f / Math::Random::weakRandInt(95, 100);

                eventsOut.emit(std::make_unique<EntityBackendEvent>(
                    context.id, std::move(shootSoundEvent)));
            }
        }
    }
    if (r_input.getInput(InputID::Reload)->wasPressed())
    {
        if (current)
        {
            if (auto *reloadable = dynamic_cast<IReloadable *>(current))
            {
                bool reloaded = reloadable->reload();

                if (reloaded)
                {
                    auto reloadSoundEvent =
                        std::make_unique<BackendPlaySoundEvent>();
                    reloadSoundEvent->soundID = reloadable->getReloadSound();
                    reloadSoundEvent->settings.volume = 0.2f;
                    reloadSoundEvent->settings.pitch =
                        100.0f / Math::Random::weakRandInt(95, 100);

                    eventsOut.emit(std::make_unique<EntityBackendEvent>(
                        context.id, std::move(reloadSoundEvent)));
                }
            }
        }
    }

    m_bodyHandler.update(context);

    if (current)
    {
        current->update(context.dt);
    }

    if (std::abs(m_body.getVelocity().x) > 0.2f &&
        m_body.getPosition().x - m_body.getLastPosition().x != 0)
    {
        m_sprite.switchAnimation(PlayerAnimation::Run);
    }
    else
    {
        m_sprite.switchAnimation(PlayerAnimation::Idle);
    }

    m_sprite.update(context.dt);
}
