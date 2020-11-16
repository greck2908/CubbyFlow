// This code is based on Jet framework.
// Copyright (c) 2018 Doyub Kim
// CubbyFlow is voxel-based fluid simulation engine for computer games.
// Copyright (c) 2020 CubbyFlow Team
// Core Part: Chris Ohk, Junwoo Hwang, Jihong Sin, Seungwoo Yoo
// AI Part: Dongheon Cho, Minseo Kim
// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef CUBBYFLOW_MPM_SOLVER3_HPP
#define CUBBYFLOW_MPM_SOLVER3_HPP

#include <Core/Solver/Grid/GridFluidSolver3.hpp>

namespace CubbyFlow
{
//!
//! \brief 3-D Material Point Method (MPM) implementation.
//!
//! This class implements 3-D Material Point Method (MPM) method by inheriting
//! GridFluidSolver3. Since it is a grid-particle hybrid method, the solver
//! also has a particle system to track fluid particles.
//!
//! \see Stomakhin et al. "A material point method for snow simulation."
//!     ACM Transactions on Graphics (TOG). Vol. 32. No. 4. ACM, 2013.
//!
class MPMSolver3 : public GridFluidSolver3
{
 public:
    class Builder;
};

//! Shared pointer type for the MPMSolver3.
using MPMSolver3Ptr = std::shared_ptr<MPMSolver3>;

//!
//! \brief Front-end to create MPMSolver3 objects step by step.
//!
class MPMSolver3::Builder final : public GridFluidSolverBuilderBase3<Builder>
{
 public:
    //! Builds MPMSolver3.
    [[nodiscard]] MPMSolver3 Build() const;

    //! Builds shared pointer of MPMSolver3 instance.
    [[nodiscard]] MPMSolver3Ptr MakeShared() const;
};
}  // namespace CubbyFlow

#endif