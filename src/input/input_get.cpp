#include "input_manager.hpp"

bool InputManager::isDown(Input input)
{
    switch (input)
    {
    case Input::Up:
        return m_up.isDown();
        break;
    case Input::Down:
        return m_down.isDown();
        break;
    case Input::Left:
        return m_left.isDown();
        break;
    case Input::Right:
        return m_right.isDown();
        break;

    case Input::Action1:
        return m_action1.isDown();
        break;
    case Input::Action2:
        return m_action2.isDown();
        break;
    case Input::Action3:
        return m_action3.isDown();
        break;
    case Input::Action4:
        return m_action4.isDown();
        break;

    case Input::Debug1:
        return m_debug1.isDown();
        break;
    case Input::Debug2:
        return m_debug2.isDown();
        break;
    case Input::Debug3:
        return m_debug3.isDown();
        break;
    case Input::Debug4:
        return m_debug4.isDown();
        break;
    case Input::Debug5:
        return m_debug5.isDown();
        break;
    case Input::Debug6:
        return m_debug6.isDown();
        break;
    default:
        return false;
        break;
    }
}

bool InputManager::wasPressed(Input input)
{
    switch (input)
    {
    case Input::Up:
        return m_up.wasPressed();
        break;
    case Input::Down:
        return m_down.wasPressed();
        break;
    case Input::Left:
        return m_left.wasPressed();
        break;
    case Input::Right:
        return m_right.wasPressed();
        break;

    case Input::Action1:
        return m_action1.wasPressed();
        break;
    case Input::Action2:
        return m_action2.wasPressed();
        break;
    case Input::Action3:
        return m_action3.wasPressed();
        break;
    case Input::Action4:
        return m_action4.wasPressed();
        break;

    case Input::Debug1:
        return m_debug1.wasPressed();
        break;
    case Input::Debug2:
        return m_debug2.wasPressed();
        break;
    case Input::Debug3:
        return m_debug3.wasPressed();
        break;
    case Input::Debug4:
        return m_debug4.wasPressed();
        break;
    case Input::Debug5:
        return m_debug5.wasPressed();
        break;
    case Input::Debug6:
        return m_debug6.wasPressed();
        break;
    default:
        return false;
        break;
    }
}