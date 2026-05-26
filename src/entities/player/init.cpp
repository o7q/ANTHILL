#include "player.hpp"

Player::Player(InputHandler &input, const Assets &assets)
    : Entity(), r_input(input), r_assets(assets), m_bodyHandler(m_body, m_collider), m_sprite(assets)
{
    m_collider.addRect({}, {3, 21});
    m_metadata.type = EntityType::Player;

    m_metadata.name = "Player";

    m_body.setTargetDamping({0.5f, 0.9725f});

    m_comboTimer.setDurationInSeconds(1.0f);
}
