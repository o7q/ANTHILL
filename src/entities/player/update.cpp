#include "entity/world_interaction/against.hpp"
#include "item/reloadable.hpp"
#include "math/rectangle.hpp"
#include "player.hpp"

void Player::update(const EntityUpdateContext &context)
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
        m_body.getPosition(), m_boundingBox, context.world,
        RectangleSide::Bottom);

    m_jumpHandler.update(context.dt, onGround);

    if (m_jumpHandler.canJump())
    {
        m_body.setVelocityY(-m_jumpHandler.getJumpPower());
    }

    Item *current = m_inventory.getSelectedItem();
    if (r_input.getInput(InputID::Action1)->wasPressed())
    {
        if (current)
        {
            current->startUsing();
        }
    }
    if (r_input.getInput(InputID::Action1)->wasUnpressed())
    {
        if (current)
        {
            current->stopUsing();
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

    if (current)
    {
        ItemOwnerContext ownerContext{getID(), m_eventEmitter,
                                      m_body.getPosition(), m_angle};
        current->update(context, ownerContext);
    }

    m_bodyHandler.update(context);
}
