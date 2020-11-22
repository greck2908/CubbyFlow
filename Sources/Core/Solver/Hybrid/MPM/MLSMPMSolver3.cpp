// This code is based on Jet framework.
// Copyright (c) 2018 Doyub Kim
// CubbyFlow is voxel-based fluid simulation engine for computer games.
// Copyright (c) 2020 CubbyFlow Team
// Core Part: Chris Ohk, Junwoo Hwang, Jihong Sin, Seungwoo Yoo
// AI Part: Dongheon Cho, Minseo Kim
// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Core/Solver/Hybrid/MPM/MLSMPMSolver3.hpp>

namespace CubbyFlow
{
MLSMPMSolver3::MLSMPMSolver3()
    : MLSMPMSolver3{ { 1, 1, 1 }, { 1, 1, 1 }, { 0, 0, 0 } }
{
    // Do nothing
}

MLSMPMSolver3::MLSMPMSolver3(const Size3& resolution,
                             const Vector3D& gridSpacing,
                             const Vector3D& gridOrigin)
    : MPMSolver3{ resolution, gridSpacing, gridOrigin }
{
    // Do nothing
}

MLSMPMSolver3::Builder MLSMPMSolver3::GetBuilder()
{
    return Builder{};
}

MLSMPMSolver3 MLSMPMSolver3::Builder::Build() const
{
    return MLSMPMSolver3{ m_resolution, GetGridSpacing(), m_gridOrigin };
}

MLSMPMSolver3Ptr MLSMPMSolver3::Builder::MakeShared() const
{
    return std::shared_ptr<MLSMPMSolver3>(
        new MLSMPMSolver3{ m_resolution, GetGridSpacing(), m_gridOrigin },
        [](MLSMPMSolver3* obj) { delete obj; });
}
}  // namespace CubbyFlow