#pragma once

#include "entity/update_context.hpp"
#include "utils/data_structures/index_2d.hpp"
#include "utils/pathfinding/a_star.hpp"
#include <functional>

class AINavigation
{
  public:
    struct Config
    {
        int astarMaxIterations = 50000;
        int astarTerminationDistance = 0;
        int astarIterationsPerFrame = 100;
        int checkpointEatRadius = 4;
        int stuckTemper = 100;
        std::function<bool(const EntityUpdateContext &, Index2D)>
            astarNeighborCheckFunction;
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

        bool operator==(const Checkpoint &other)
        {
            return pos == other.pos && axis == other.axis;
        }

        bool operator!=(const Checkpoint &other)
        {
            return pos != other.pos || axis != other.axis;
        }
    };

  public:
    AINavigation() = default;
    virtual ~AINavigation() = default;

    void update(Vec2i currentPos, const EntityUpdateContext &context);
    void setGoal(Vec2i end) { m_astarGoalPosition = end; }

    void setConfig(Config config)
    {
        m_config = config;
        m_astar.setMaxIterations(config.astarMaxIterations);
        m_astar.setTerminateDistance(config.astarTerminationDistance);
    }

    std::optional<Vec2i> getMoveVector() const { return m_moveVector; }

    const std::vector<Checkpoint> &getCheckpoints() const
    {
        return m_checkpoints;
    }

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
    int m_stuckCounter = 0;
    int m_stuckRetryCounter = 0;
    bool m_isStuck = false;
    std::optional<Vec2i> m_moveVector;
};
