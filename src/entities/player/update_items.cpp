#include "item/reloadable.hpp"
#include "player.hpp"

void Player::update_items(const EntityUpdateContext &context,
                          EventPool<EntityEvent> &eventsOut)
{
    Item *current = m_inventory.getSelectedItem();

    if (!current)
    {
        return;
    }

    ItemUseContext itemContext;
    itemContext.ownerID = context.id;
    itemContext.heldPosition = m_body.getPosition();
    itemContext.heldAngle = m_angle;

    if (r_input.getInput(InputID::Shoot)->isDown())
    {
        current->use(itemContext, eventsOut);
    }
    if (r_input.getInput(InputID::Reload)->wasPressed())
    {
        if (auto *reloadable = dynamic_cast<IReloadable *>(current))
        {
            reloadable->reload(itemContext, eventsOut);
        }
    }

    current->update(context.dt);
}
