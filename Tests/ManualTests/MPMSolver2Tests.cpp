#include "pch.hpp"

#include <ManualTests.hpp>

#include <Core/Emitter/VolumeParticleEmitter2.hpp>
#include <Core/Geometry/Box2.hpp>
#include <Core/Solver/Hybrid/MPM/MPMSolver2.hpp>

using namespace CubbyFlow;

CUBBYFLOW_TESTS(MPMSolver2);

CUBBYFLOW_BEGIN_TEST_F(MPMSolver2, SteadyState)
{
    // Build solver
    auto solver = MPMSolver2::Builder()
                      .WithResolution({ 32, 32 })
                      .WithDomainSizeX(1.0)
                      .MakeShared();

    // Build emitter
    auto box = Box2::Builder()
                   .WithLowerCorner({ 0.0, 0.0 })
                   .WithUpperCorner({ 1.0, 0.5 })
                   .MakeShared();

    auto emitter = VolumeParticleEmitter2::Builder()
                       .WithSurface(box)
                       .WithSpacing(1.0 / 64.0)
                       .WithIsOneShot(true)
                       .MakeShared();

    solver->SetParticleEmitter(emitter);

    for (Frame frame; frame.index < 120; ++frame)
    {
        solver->Update(frame);

        SaveParticleDataXY(solver->GetParticleSystemData(), frame.index);
    }
}
CUBBYFLOW_END_TEST_F