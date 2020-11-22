// This code is based on Jet framework.
// Copyright (c) 2018 Doyub Kim
// CubbyFlow is voxel-based fluid simulation engine for computer games.
// Copyright (c) 2020 CubbyFlow Team
// Core Part: Chris Ohk, Junwoo Hwang, Jihong Sin, Seungwoo Yoo
// AI Part: Dongheon Cho, Minseo Kim
// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Core/Solver/Hybrid/MPM/MPMSolver3.hpp>

namespace CubbyFlow
{
MPMSolver3::MPMSolver3() : MPMSolver3{ { 1, 1, 1 }, { 1, 1, 1 }, { 0, 0, 0 } }
{
    // Do nothing
}

MPMSolver3::MPMSolver3(const Size3& resolution, const Vector3D& gridSpacing,
                       const Vector3D& gridOrigin)
    : GridFluidSolver3{ resolution, gridSpacing, gridOrigin }
{
    // Do nothing
}

MPMSolver3::Builder MPMSolver3::GetBuilder()
{
    return Builder{};
}

MPMSolver3 MPMSolver3::Builder::Build() const
{
    return MPMSolver3{ m_resolution, GetGridSpacing(), m_gridOrigin };
}

MPMSolver3Ptr MPMSolver3::Builder::MakeShared() const
{
    return std::shared_ptr<MPMSolver3>(
        new MPMSolver3{ m_resolution, GetGridSpacing(), m_gridOrigin },
        [](MPMSolver3* obj) { delete obj; });
}
}  // namespace CubbyFlow