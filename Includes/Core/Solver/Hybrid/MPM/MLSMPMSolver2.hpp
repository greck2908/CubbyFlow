// This code is based on Jet framework.
// Copyright (c) 2018 Doyub Kim
// CubbyFlow is voxel-based fluid simulation engine for computer games.
// Copyright (c) 2020 CubbyFlow Team
// Core Part: Chris Ohk, Junwoo Hwang, Jihong Sin, Seungwoo Yoo
// AI Part: Dongheon Cho, Minseo Kim
// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef CUBBYFLOW_MLSMPM_SOLVER2_HPP
#define CUBBYFLOW_MLSMPM_SOLVER2_HPP

#include <Core/Solver/Hybrid/MPM/MPMSolver2.hpp>

namespace CubbyFlow
{
//!
//! \brief 2-D Moving Least Squares Material Point Method (MLS-MPM)
//!        implementation.
//!
//! This class implements 2-D Moving Least Squares Material Point Method
//! (MLS-MPM) method by inheriting MPMSolver2. Since it is a grid-particle
//! hybrid method, the solver also has a particle system to track fluid
//! particles.
//!
//! \see Hu Yuanming et al. "A moving least squares material point method with
//!      displacement discontinuity and two-way rigid body coupling."
//!     ACM Transactions on Graphics (TOG). Vol. 37. No. 4. ACM, 2018.
//!
class MLSMPMSolver2 : public MPMSolver2
{
 public:
    class Builder;

    //! Default constructor.
    MLSMPMSolver2();

    //! Constructs solver with initial grid size.
    MLSMPMSolver2(const Size2& resolution, const Vector2D& gridSpacing,
                  const Vector2D& gridOrigin);

    //! Deleted copy constructor.
    MLSMPMSolver2(const MLSMPMSolver2&) = delete;

    //! Deleted move constructor.
    MLSMPMSolver2(MLSMPMSolver2&&) noexcept = delete;

    //! Default virtual destructor.
    ~MLSMPMSolver2() override = default;

    //! Deleted copy assignment operator.
    MLSMPMSolver2& operator=(const MLSMPMSolver2&) = delete;

    //! Deleted move assignment operator.
    MLSMPMSolver2& operator=(MLSMPMSolver2&&) noexcept = delete;

    //! Returns builder for MLSMPMSolver2.
    [[nodiscard]] static Builder GetBuilder();
};

//! Shared pointer type for the MLSMPMSolver2.
using MLSMPMSolver2Ptr = std::shared_ptr<MLSMPMSolver2>;

//!
//! \brief Front-end to create MLSMPMSolver2 objects step by step.
//!
class MLSMPMSolver2::Builder final : public GridFluidSolverBuilderBase2<Builder>
{
 public:
    //! Builds MLSMPMSolver2.
    [[nodiscard]] MLSMPMSolver2 Build() const;

    //! Builds shared pointer of MLSMPMSolver2 instance.
    [[nodiscard]] MLSMPMSolver2Ptr MakeShared() const;
};
}  // namespace CubbyFlow

#endif