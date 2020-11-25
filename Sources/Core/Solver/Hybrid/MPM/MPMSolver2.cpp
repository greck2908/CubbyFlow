// This code is based on Jet framework.
// Copyright (c) 2018 Doyub Kim
// CubbyFlow is voxel-based fluid simulation engine for computer games.
// Copyright (c) 2020 CubbyFlow Team
// Core Part: Chris Ohk, Junwoo Hwang, Jihong Sin, Seungwoo Yoo
// AI Part: Dongheon Cho, Minseo Kim
// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Core/Solver/Hybrid/MPM/MPMSolver2.hpp>
#include <Core/Utils/Logging.hpp>
#include <Core/Utils/Timer.hpp>

namespace CubbyFlow
{
MPMSolver2::MPMSolver2() : MPMSolver2{ { 1, 1 }, { 1, 1 }, { 0, 0 } }
{
    // Do nothing
}

MPMSolver2::MPMSolver2(const Size2& resolution, const Vector2D& gridSpacing,
                       const Vector2D& gridOrigin)
    : GridFluidSolver2{ resolution, gridSpacing, gridOrigin }
{
    m_particles = std::make_shared<ParticleSystemData2>();
    m_deformationGradientID = m_particles->AddMatrixData(Matrix2x2D{ 1.0 });
    m_detDeformationGradientID = m_particles->AddScalarData(1.0);
}

double MPMSolver2::GetSnowHardeningFactor() const
{
    return m_snowHardeningFactor;
}

void MPMSolver2::SetSnowHardeningFactor(double newFactor)
{
    m_snowHardeningFactor = newFactor;
}

double MPMSolver2::GetYoungsModulus() const
{
    return m_youngsModulus;
}

void MPMSolver2::SetYoungsModulus(double newModulus)
{
    m_youngsModulus = newModulus;
}

double MPMSolver2::GetPoissonRatio() const
{
    return m_poissonRatio;
}

void MPMSolver2::SetPoissonRatio(double newRatio)
{
    m_poissonRatio = newRatio;
}

ArrayAccessor1<Matrix2x2D> MPMSolver2::GetDeformationGradient() const
{
    return m_particles->MatrixDataAt(m_deformationGradientID);
}

ArrayAccessor1<double> MPMSolver2::GetDetDeformationGradient() const
{
    return m_particles->ScalarDataAt(m_detDeformationGradientID);
}

const ParticleSystemData2Ptr& MPMSolver2::GetParticleSystemData() const
{
    return m_particles;
}

const ParticleEmitter2Ptr& MPMSolver2::GetParticleEmitter() const
{
    return m_particleEmitter;
}

void MPMSolver2::SetParticleEmitter(const ParticleEmitter2Ptr& newEmitter)
{
    m_particleEmitter = newEmitter;
    newEmitter->SetTarget(m_particles);
}

void MPMSolver2::OnInitialize()
{
    GridFluidSolver2::OnInitialize();

    const Timer timer;
    UpdateParticleEmitter(0.0);
    CUBBYFLOW_INFO << "Update particle emitter took "
                   << timer.DurationInSeconds() << " seconds";
}

void MPMSolver2::OnBeginAdvanceTimeStep(double timeIntervalInSeconds)
{
    Timer timer;
    UpdateParticleEmitter(timeIntervalInSeconds);
    CUBBYFLOW_INFO << "Update particle emitter took "
                   << timer.DurationInSeconds() << " seconds";

    CUBBYFLOW_INFO << "Number of MPM-type particles: "
                   << m_particles->GetNumberOfParticles();

    timer.Reset();
    TransferFromParticlesToGrids();
    CUBBYFLOW_INFO << "TransferFromParticlesToGrids took "
                   << timer.DurationInSeconds() << " seconds";
}

void MPMSolver2::ComputeAdvection(double timeIntervalInSeconds)
{
    UNUSED_VARIABLE(timeIntervalInSeconds);

    const Timer timer;
    TransferFromGridsToParticles();
    CUBBYFLOW_INFO << "TransferFromGridsToParticles took "
                   << timer.DurationInSeconds() << " seconds";
}

void MPMSolver2::TransferFromParticlesToGrids()
{
    ArrayAccessor1<Vector2<double>> positions = m_particles->GetPositions();
    ArrayAccessor1<Vector2<double>> velocities = m_particles->GetVelocities();
    ArrayAccessor1<double> detDeformationGradients =
        GetDetDeformationGradient();
    const size_t numberOfParticles = m_particles->GetNumberOfParticles();

    const double dx =
        1.0 / static_cast<double>(GetGridSystemData()->GetResolution().x);
    const double invDx = 1.0 / dx;

    // Initial Lamé parameters
    const double mu_0 = GetYoungsModulus() / (2 * (1 + GetPoissonRatio()));
    const double lambda_0 =
        GetYoungsModulus() * GetPoissonRatio() /
        ((1 + GetPoissonRatio()) * (1 - 2 * GetPoissonRatio()));

    for (size_t i = 0; i < numberOfParticles; ++i)
    {
        // Element-wise floor
        Vector2D baseCoord =
            Floor(positions[i].x * invDx - Vector2D{ 0.5, 0.5 });
        Vector2D fx = positions[i].x * invDx - baseCoord;

        // Quadratic kernels
        // [http://mpm.graphics Eq. 123, with x=fx,fx-1,fx-2]
        Vector2D w[3] = {
            Vector2D{ 0.5, 0.5 } * Sqrt(Vector2D{ 1.5, 1.5 }.Sub(fx)),
            Vector2D{ 0.75, 0.75 } - Sqrt(fx.Sub(Vector2D{ 1.0, 1.0 })),
            Vector2D{ 0.5, 0.5 } - Sqrt(fx.Sub(Vector2D{ 0.5, 0.5 }))
        };

        // Compute current Lamé parameters
        // [http://mpm.graphics Eqn. 86]
        double e = std::exp(m_snowHardeningFactor *
                            (1.0 - detDeformationGradients[i]));
        double mu = mu_0 * e;
        double lambda = lambda_0 * e;

        (void)mu;
        (void)lambda;
    }

    (void)velocities;
}

void MPMSolver2::TransferFromGridsToParticles()
{
}

void MPMSolver2::UpdateParticleEmitter(double timeIntervalInSeconds) const
{
    if (m_particleEmitter != nullptr)
    {
        m_particleEmitter->Update(GetCurrentTimeInSeconds(),
                                  timeIntervalInSeconds);
    }
}

MPMSolver2::Builder MPMSolver2::GetBuilder()
{
    return Builder{};
}

MPMSolver2 MPMSolver2::Builder::Build() const
{
    return MPMSolver2{ m_resolution, GetGridSpacing(), m_gridOrigin };
}

MPMSolver2Ptr MPMSolver2::Builder::MakeShared() const
{
    return std::shared_ptr<MPMSolver2>(
        new MPMSolver2{ m_resolution, GetGridSpacing(), m_gridOrigin },
        [](MPMSolver2* obj) { delete obj; });
}
}  // namespace CubbyFlow