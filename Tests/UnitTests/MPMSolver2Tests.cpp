#include "pch.hpp"

#include <Core/Solver/Hybrid/MPM/MPMSolver2.hpp>

using namespace CubbyFlow;

TEST(MPMSolver2, UpdateEmpty)
{
    MPMSolver2 solver;

    for (Frame frame; frame.index < 2; ++frame)
    {
        solver.Update(frame);
    }
}