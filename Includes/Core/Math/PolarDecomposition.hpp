// This code is based on Jet framework.
// Copyright (c) 2018 Doyub Kim
// CubbyFlow is voxel-based fluid simulation engine for computer games.
// Copyright (c) 2020 CubbyFlow Team
// Core Part: Chris Ohk, Junwoo Hwang, Jihong Sin, Seungwoo Yoo
// AI Part: Dongheon Cho, Minseo Kim
// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef CUBBYFLOW_POLAR_DECOMPOSITION_HPP
#define CUBBYFLOW_POLAR_DECOMPOSITION_HPP

#include <Core/Matrix/Matrix2x2.hpp>

namespace CubbyFlow
{
//!
//! \brief Polar decomposition.
//!
//! This function decompose the input matrix \p m to \p r * \p s.
//!
//! \tparam T Real-value type.
//!
//! \param m The input matrix to decompose.
//! \param r A unitary matrix.
//! \param s A positive-semidefinite Hermitian matrix,
//!          both square and of the same size.
//!
template <typename T>
void PolarDecomposition(const Matrix2x2<T>& m, Matrix2x2<T>& r,
                        Matrix2x2<T>& s);
}  // namespace CubbyFlow

#include <Core/Math/PolarDecomposition-Impl.hpp>

#endif