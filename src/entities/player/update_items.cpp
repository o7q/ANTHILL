#include "player.hpp"

#include "item/reloadable.hpp"

void Player::update_items(const EntityUpdateContext &context, EventPool<EntityEvent> &eventsOut)
{
    Item *currentItem = m_inventory.getSelectedItem();

    if (!currentItem)
    {
        return;
    }

    ItemUseContext itemContext;
    itemContext.ownerID      = context.id;
    itemContext.heldPosition = m_body.getPosition();
    itemContext.heldAngle    = m_angle;

    if (r_input.getInput(InputID::Shoot)->isDown())
    {
        currentItem->use(itemContext, eventsOut);
    }
    if (r_input.getInput(InputID::Reload)->wasPressed())
    {
        if (auto *reloadableItem = dynamic_cast<IReloadable *>(currentItem))
        {
            reloadableItem->reload();
        }
    }

    currentItem->update(context.time.dt);
}
