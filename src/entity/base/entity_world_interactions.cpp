#include "entity.hpp"

void Entity::handleWorldInteraction(float dt)
{
    Vec2<int> pos = m_body.getPosition();
    Vec2<int> a = m_collisionBox.getBoundingBox().getA() + pos;
    Vec2<int> b = m_collisionBox.getBoundingBox().getB() + pos;

    int solidCount = 0;
    auto query = [&](Particle *p)
    {
        if (p->isSolid() && !p->inMotion())
        {
            solidCount++;
            return true;
        }
        return false;
    };
    r_world.getParticleHandler().query(a, b, query);

    if (solidCount > 0)
    {
    }
    else
    {
        Vec2<int> start = m_body.getPosition();
        m_body.update(dt);
        Vec2<int> end = m_body.getPosition();
        Vec2<int> collisionResponse =
            m_collisionBox.getWorldHandler()
                .calculateAvoidedWorldCollisionPosition(start, end);

        m_body.setPosition(collisionResponse.x, collisionResponse.y);
    }
}
