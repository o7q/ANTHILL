#pragma once

#include "entity/update_context.hpp"
#include "px/a_star/a_star.hpp"
#include <functional>

class AINavigation
{
  public:
    struct Config
    {
        px::AStarSolver::Config astar;
        int iterationsPerFrame     = 100;
        int checkpointEatRadius    = 4;
        float maxStuckTime         = 1.0f;
        float satisfactoryDistance = 20.0f;
        std::function<bool(const EntityUpdateContext &, px::Vec2i)> astarNeighborCheckFunction;
    };

    enum class PathState
    {
        Idle,
        Iterating,
        Ready
    };

    enum class Axis
    {
        Vertical,
        Horizontal
    };

    struct Checkpoint
    {
        px::Vec2i pos;
        Axis axis;

        bool operator==(const Checkpoint &other) { return pos == other.pos && axis == other.axis; }

        bool operator!=(const Checkpoint &other) { return pos != other.pos || axis != other.axis; }
    };

  public:
    AINavigation()          = default;
    virtual ~AINavigation() = default;

    void update(px::Vec2i currentPos, const EntityUpdateContext &context);
    void setGoal(px::Vec2i goal) { m_astarGoalPosition = goal; }

    void setConfig(Config config)
    {
        m_config = config;
        m_astar.setConfig(config.astar);
        m_stuckTimer.setDurationInSeconds(config.maxStuckTime);
    }

    std::optional<px::Vec2i> getMoveVector() const { return m_moveVector; }

    const std::vector<Checkpoint> &getCheckpoints() const { return m_checkpoints; }

    std::vector<px::Vec2i> generatePath() { return m_astar.generatePath(); }

  private:
    void update_path(px::Vec2i currentPos, const EntityUpdateContext &context);

    std::optional<Checkpoint> get_next_movement_checkpoint(px::Vec2i currentPos);
    void update_movement(px::Vec2i currentPos);

  private:
    Config m_config;

    px::AStarSolver m_astar;
    PathState m_astarPathState = PathState::Idle;
    px::Vec2i m_astarGoalPosition;
    std::vector<Checkpoint> m_checkpoints;

    Checkpoint m_previousCheckpoint;
    px::Timer m_stuckTimer;
    std::optional<px::Vec2i> m_moveVector;
};
