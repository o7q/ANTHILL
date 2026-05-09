#pragma once

#include <vector>

class Input
{
  public:
    enum class ButtonType
    {
        Key,
        Mouse
    };

    struct Bind
    {
        ButtonType type;
        unsigned int id;

        bool operator==(const Bind &other) const { return type == other.type && id == other.id; }
    };

  public:
    Input() = default;

    void poll(Bind bind, bool isDown);

    void update();

    void assignBind(const Bind &bind);
    void removeBind(const Bind &bind);
    void removeBindsOfType(ButtonType type);

    bool isDown() const { return m_down; }
    bool wasDown() const { return m_wasDown; }
    bool wasPressed() const { return m_pressed; }
    bool wasUnpressed() const { return m_unpressed; }

  private:
    std::vector<Bind> m_binds;

    bool m_down      = false;
    bool m_wasDown   = false;
    bool m_pressed   = false;
    bool m_unpressed = false;
};
