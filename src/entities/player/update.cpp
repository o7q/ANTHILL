#include "player.hpp"

void Player::update(const EntityUpdateContext &context)
{
    if (r_input.getInput(InputID::Left)->isDown())
    {
        m_body.setVelocityX(-7);
    }
    if (r_input.getInput(InputID::Right)->isDown())
    {
        m_body.setVelocityX(7);
    }
    if (r_input.getInput(InputID::Left)->wasUnpressed())
    {
        m_body.setVelocityX(0);
    }
    if (r_input.getInput(InputID::Right)->wasUnpressed())
    {
        m_body.setVelocityX(0);
    }
    if (r_input.getInput(InputID::Jump)->wasPressed())
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

    if (current)
    {
        ItemOwnerContext ownerContext{getID(), m_eventEmitter,
                                      m_body.getPosition(), m_angle};
        current->update(context, ownerContext);
    }

    bool onGround = m_interactionBox.getWorldHandler().againstSolidSurface(
        m_body.getPosition(), RectangleSide::Bottom, context.particles);
    m_jumpHandler.update(context.dt, onGround);

    updateMotion(context);
    updateHealth();
}
