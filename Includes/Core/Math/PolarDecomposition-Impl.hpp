// This code is based on Jet framework.
// Copyright (c) 2018 Doyub Kim
// CubbyFlow is voxel-based fluid simulation engine for computer games.
// Copyright (c) 2020 CubbyFlow Team
// Core Part: Chris Ohk, Junwoo Hwang, Jihong Sin, Seungwoo Yoo
// AI Part: Dongheon Cho, Minseo Kim
// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef CUBBYFLOW_POLAR_DECOMPOSITION_IMPL_HPP
#define CUBBYFLOW_POLAR_DECOMPOSITION_IMPL_HPP

namespace CubbyFlow
{
template <typename T>
void PolarDecomposition(const Matrix2x2<T>& m, Matrix2x2<T>& r, Matrix2x2<T>& s)
{
    T x = m(0, 0) + m(1, 1);
    T y = m(1, 0) - m(0, 1);
    T scale = 1.0 / std::sqrt(x * x + y * y);
    T xScale = x * scale, yScale = y * scale;

    r(0, 0) = xScale;
    r(0, 1) = -yScale;
    r(1, 0) = yScale;
    r(1, 1) = xScale;

    s = r.Transposed() * m;
}
}  // namespace CubbyFlow

#endif