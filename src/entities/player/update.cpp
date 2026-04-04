#include "entity/world_interaction/against.hpp"
#include "item/context.hpp"
#include "item/reloadable.hpp"
#include "math/rectangle.hpp"
#include "player.hpp"

EventPool<EntityEvent> Player::update(const EntityUpdateContext &context)
{
    EventPool<EntityEvent> events;

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
        m_body.getPosition(), m_boundingBox, context.world,
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
            ItemUseContext context;
            context.ownerID = getID();
            context.heldPosition = m_body.getPosition();
            context.heldAngle = m_angle;

            for (auto &event : current->use(context))
            {
                events.emit(std::move(event));
            }
        }
    }
    if (r_input.getInput(InputID::Reload)->wasPressed())
    {
        if (current)
        {
            if (auto *reloadable = dynamic_cast<IReloadable *>(current))
            {
                reloadable->reload();
            }
        }
    }

    m_bodyHandler.update(context);

    if (current)
    {
        current->update(context.dt);
    }

    return events;
}
