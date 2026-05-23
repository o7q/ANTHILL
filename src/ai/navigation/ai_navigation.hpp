#pragma once

#include "core/ai/a_star.hpp"
#include "entity/update_context.hpp"
#include <functional>

class AINavigation
{
  public:
    struct Config
    {
        AStarSolver::Config astar;
        int iterationsPerFrame     = 100;
        int checkpointEatRadius    = 4;
        float maxStuckTime         = 1.0f;
        float satisfactoryDistance = 20.0f;
        std::function<bool(const EntityUpdateContext &, Vec2i)> astarNeighborCheckFunction;
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
        Vec2i pos;
        Axis axis;

        bool operator==(const Checkpoint &other) { return pos == other.pos && axis == other.axis; }

        bool operator!=(const Checkpoint &other) { return pos != other.pos || axis != other.axis; }
    };

  public:
    AINavigation()          = default;
    virtual ~AINavigation() = default;

    void update(Vec2i currentPos, const EntityUpdateContext &context);
    void setGoal(Vec2i goal) { m_astarGoalPosition = goal; }

    void setConfig(Config config)
    {
        m_config = config;
        m_astar.setConfig(config.astar);
        m_stuckTimer.setDurationInSeconds(config.maxStuckTime);
    }

    std::optional<Vec2i> getMoveVector() const { return m_moveVector; }

    const std::vector<Checkpoint> &getCheckpoints() const { return m_checkpoints; }

    std::vector<Vec2i> generatePath() { return m_astar.generatePath(); }

  private:
    void update_path(Vec2i currentPos, const EntityUpdateContext &context);

    std::optional<Checkpoint> get_next_movement_checkpoint(Vec2i currentPos);
    void update_movement(Vec2i currentPos);

  private:
    Config m_config;

    AStarSolver m_astar;
    PathState m_astarPathState = PathState::Idle;
    Vec2i m_astarGoalPosition;
    std::vector<Checkpoint> m_checkpoints;

    Checkpoint m_previousCheckpoint;
    Timer m_stuckTimer;
    std::optional<Vec2i> m_moveVector;
};
