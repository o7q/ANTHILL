#include "player.hpp"

Player::Player(InputHandler &input, const Assets &assets)
    : r_input(input), r_assets(assets), m_bodyHandler(m_body, m_collider)
{
    m_collider.addRect({}, {3, 21});
    m_metadata.type = EntityType::Player;

    m_metadata.name = "Player";

    m_jumpHandler.setHoldLength(0.3f);
    m_jumpHandler.setJumpPower(5.0f);

    m_body.setTargetDamping({0.5f, 0.94f});
}
