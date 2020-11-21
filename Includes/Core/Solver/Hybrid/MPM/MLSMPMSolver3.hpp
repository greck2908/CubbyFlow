// This code is based on Jet framework.
// Copyright (c) 2018 Doyub Kim
// CubbyFlow is voxel-based fluid simulation engine for computer games.
// Copyright (c) 2020 CubbyFlow Team
// Core Part: Chris Ohk, Junwoo Hwang, Jihong Sin, Seungwoo Yoo
// AI Part: Dongheon Cho, Minseo Kim
// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef CUBBYFLOW_MLSMPM_SOLVER3_HPP
#define CUBBYFLOW_MLSMPM_SOLVER3_HPP

#include <Core/Solver/Hybrid/MPM/MPMSolver3.hpp>

namespace CubbyFlow
{
//!
//! \brief 3-D Moving Least Squares Material Point Method (MLS-MPM)
//!        implementation.
//!
//! This class implements 3-D Moving Least Squares Material Point Method
//! (MLS-MPM) method by inheriting MPMSolver3. Since it is a grid-particle
//! hybrid method, the solver also has a particle system to track fluid
//! particles.
//!
//! \see Hu Yuanming et al. "A moving least squares material point method with
//!      displacement discontinuity and two-way rigid body coupling."
//!     ACM Transactions on Graphics (TOG). Vol. 37. No. 4. ACM, 2018.
//!
class MLSMPMSolver3 : public MPMSolver3
{
 public:
    class Builder;
};

//! Shared pointer type for the MLSMPMSolver3.
using MLSMPMSolver3Ptr = std::shared_ptr<MLSMPMSolver3>;

//!
//! \brief Front-end to create MLSMPMSolver3 objects step by step.
//!
class MLSMPMSolver3::Builder final : public GridFluidSolverBuilderBase3<Builder>
{
 public:
    //! Builds MLSMPMSolver3.
    [[nodiscard]] MLSMPMSolver3 Build() const;

    //! Builds shared pointer of MLSMPMSolver3 instance.
    [[nodiscard]] MLSMPMSolver3Ptr MakeShared() const;
};
}  // namespace CubbyFlow

#endif