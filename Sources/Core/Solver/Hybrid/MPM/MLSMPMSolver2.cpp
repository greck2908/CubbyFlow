// This code is based on Jet framework.
// Copyright (c) 2018 Doyub Kim
// CubbyFlow is voxel-based fluid simulation engine for computer games.
// Copyright (c) 2020 CubbyFlow Team
// Core Part: Chris Ohk, Junwoo Hwang, Jihong Sin, Seungwoo Yoo
// AI Part: Dongheon Cho, Minseo Kim
// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Core/Solver/Hybrid/MPM/MLSMPMSolver2.hpp>

namespace CubbyFlow
{
MLSMPMSolver2::MLSMPMSolver2() : MLSMPMSolver2{ { 1, 1 }, { 1, 1 }, { 0, 0 } }
{
    // Do nothing
}

MLSMPMSolver2::MLSMPMSolver2(const Size2& resolution,
                             const Vector2D& gridSpacing,
                             const Vector2D& gridOrigin)
    : MPMSolver2{ resolution, gridSpacing, gridOrigin }
{
    // Do nothing
}

MLSMPMSolver2::Builder MLSMPMSolver2::GetBuilder()
{
    return Builder{};
}

MLSMPMSolver2 MLSMPMSolver2::Builder::Build() const
{
    return MLSMPMSolver2{ m_resolution, GetGridSpacing(), m_gridOrigin };
}

MLSMPMSolver2Ptr MLSMPMSolver2::Builder::MakeShared() const
{
    return std::shared_ptr<MLSMPMSolver2>(
        new MLSMPMSolver2{ m_resolution, GetGridSpacing(), m_gridOrigin },
        [](MLSMPMSolver2* obj) { delete obj; });
}
}  // namespace CubbyFlow