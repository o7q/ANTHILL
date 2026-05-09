#include "player.hpp"

#include "items/weapons/shotgun.hpp"

Player::Player(InputHandler &input, const Assets &assets)
    : Entity(), r_input(input), r_assets(assets), m_bodyHandler(m_body, m_boundingBox), m_sprite(assets)
{
    m_boundingBox.setSize({3, 21});
    m_metadata.type = EntityType::Player;

    auto shotgun = std::make_unique<Shotgun>(assets);
    m_inventory.addItem(std::move(shotgun), 0);

    m_metadata.name = "Player";
}
