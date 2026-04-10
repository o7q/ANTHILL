#include "entity/world_interaction/against.hpp"
#include "events/entity/entity_backend.hpp"
#include "item/context.hpp"
#include "item/reloadable.hpp"
#include "math/random.hpp"
#include "math/rectangle.hpp"
#include "player.hpp"
#include <memory>

void Player::update(const EntityWorldContext &worldContext,
                    EventPool<EntityEvent> &eventsOut)
{
    if (r_input.getInput(InputID::Left)->isDown())
    {
        m_body.setVelocityTargetX(-5.0f);
    }
    if (r_input.getInput(InputID::Right)->isDown())
    {
        m_body.setVelocityTargetX(5.0f);
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
        m_body.getPosition(), m_boundingBox, worldContext.world,
        RectangleSide::Bottom);

    m_jumpHandler.update(worldContext.dt, onGround);

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
            itemContext.ownerID = worldContext.id;
            itemContext.heldPosition = m_body.getPosition();
            itemContext.heldAngle = m_angle;

            bool used = current->use(itemContext, eventsOut);

            if (used)
            {
                auto shootSoundEvent =
                    std::make_unique<EntityBackendPlaySoundEvent>(
                        worldContext.id);
                shootSoundEvent->backendEvent.soundID = current->getUseSound();
                shootSoundEvent->backendEvent.settings.volume = 0.2f;
                shootSoundEvent->backendEvent.settings.pitch =
                    100.0f / Math::Random::weakRandInt(95, 100);

                eventsOut.emit(std::move(shootSoundEvent));
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
                        std::make_unique<EntityBackendPlaySoundEvent>(
                            worldContext.id);
                    reloadSoundEvent->backendEvent.soundID =
                        reloadable->getReloadSound();
                    reloadSoundEvent->backendEvent.settings.volume = 0.2f;
                    reloadSoundEvent->backendEvent.settings.pitch =
                        100.0f / Math::Random::weakRandInt(95, 100);

                    eventsOut.emit(std::move(reloadSoundEvent));
                }
            }
        }
    }

    m_bodyHandler.update(worldContext);

    if (current)
    {
        current->update(worldContext.dt);
    }
}
