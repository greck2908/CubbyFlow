// This code is based on Jet framework.
// Copyright (c) 2018 Doyub Kim
// CubbyFlow is voxel-based fluid simulation engine for computer games.
// Copyright (c) 2020 CubbyFlow Team
// Core Part: Chris Ohk, Junwoo Hwang, Jihong Sin, Seungwoo Yoo
// AI Part: Dongheon Cho, Minseo Kim
// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef CUBBYFLOW_VERTEX_CENTERED_VECTOR_GRID3_HPP
#define CUBBYFLOW_VERTEX_CENTERED_VECTOR_GRID3_HPP

#include <Core/Grid/CollocatedVectorGrid3.hpp>

namespace CubbyFlow
{
//!
//! \brief 3-D Vertex-centered vector grid structure.
//!
//! This class represents 3-D vertex-centered vector grid which extends
//! CollocatedVectorGrid3. As its name suggests, the class defines the data
//! point at the grid vertices (corners). Thus, A x B x C grid resolution will
//! have (A+1) x (B+1) x (C+1) data points.
//!
class VertexCenteredVectorGrid3 final : public CollocatedVectorGrid3
{
 public:
    CUBBYFLOW_GRID3_TYPE_NAME(VertexCenteredVectorGrid3)

    class Builder;

    //! Constructs zero-sized grid.
    VertexCenteredVectorGrid3() = default;

    //! Constructs a grid with given resolution, grid spacing, origin and
    //! initial value.
    VertexCenteredVectorGrid3(size_t resolutionX, size_t resolutionY,
                              size_t resolutionZ, double gridSpacingX = 1.0,
                              double gridSpacingY = 1.0,
                              double gridSpacingZ = 1.0, double originX = 0.0,
                              double originY = 0.0, double originZ = 0.0,
                              double initialValueU = 0.0,
                              double initialValueV = 0.0,
                              double initialValueW = 0.0);

    //! Constructs a grid with given resolution, grid spacing, origin and
    //! initial value.
    VertexCenteredVectorGrid3(const Size3& resolution,
                              const Vector3D& gridSpacing = Vector3D{ 1.0, 1.0,
                                                                      1.0 },
                              const Vector3D& origin = Vector3D{},
                              const Vector3D& initialValue = Vector3D{});

    //! Copy constructor.
    VertexCenteredVectorGrid3(const VertexCenteredVectorGrid3& other);

    //! Deleted move constructor.
    VertexCenteredVectorGrid3(VertexCenteredVectorGrid3&&) noexcept = delete;

    // Default virtual destructor.
    ~VertexCenteredVectorGrid3() override = default;

    //! Sets the contents with the given \p other grid.
    VertexCenteredVectorGrid3& operator=(
        const VertexCenteredVectorGrid3& other);

    //! Deleted move assignment operator.
    VertexCenteredVectorGrid3& operator=(VertexCenteredVectorGrid3&&) noexcept =
        delete;

    //! Returns the actual data point size.
    [[nodiscard]] Size3 GetDataSize() const override;

    //! Returns data position for the grid point at (0, 0).
    //! Note that this is different from origin() since origin() returns
    //! the lower corner point of the bounding box.
    [[nodiscard]] Vector3D GetDataOrigin() const override;

    //!
    //! \brief Swaps the contents with the given \p other grid.
    //!
    //! This function swaps the contents of the grid instance with the given
    //! grid object \p other only if \p other has the same type with this grid.
    //!
    void Swap(Grid3* other) override;

    //! Sets the contents with the given \p other grid.
    void Set(const VertexCenteredVectorGrid3& other);

    //! Fills the grid with given value.
    void Fill(const Vector3D& value,
              ExecutionPolicy policy = ExecutionPolicy::Parallel) override;

    //! Fills the grid with given function.
    void Fill(const std::function<Vector3D(const Vector3D&)>& func,
              ExecutionPolicy policy = ExecutionPolicy::Parallel) override;

    //! Returns the copy of the grid instance.
    [[nodiscard]] std::shared_ptr<VectorGrid3> Clone() const override;

    //! Returns builder for VertexCenteredVectorGrid3.
    [[nodiscard]] static Builder GetBuilder();
};

//! Shared pointer for the VertexCenteredVectorGrid3 type.
using VertexCenteredVectorGrid3Ptr = std::shared_ptr<VertexCenteredVectorGrid3>;

//! A grid builder class that returns 3-D vertex-centered Vector grid.
class VertexCenteredVectorGrid3::Builder final : public VectorGridBuilder3
{
 public:
    //! Returns builder with resolution.
    [[nodiscard]] Builder& WithResolution(const Size3& resolution);

    //! Returns builder with resolution.
    [[nodiscard]] Builder& WithResolution(size_t resolutionX,
                                          size_t resolutionY,
                                          size_t resolutionZ);

    //! Returns builder with grid spacing.
    [[nodiscard]] Builder& WithGridSpacing(const Vector3D& gridSpacing);

    //! Returns builder with grid spacing.
    [[nodiscard]] Builder& WithGridSpacing(double gridSpacingX,
                                           double gridSpacingY,
                                           double gridSpacingZ);

    //! Returns builder with grid origin.
    [[nodiscard]] Builder& WithOrigin(const Vector3D& gridOrigin);

    //! Returns builder with grid origin.
    [[nodiscard]] Builder& WithOrigin(double gridOriginX, double gridOriginY,
                                      double gridOriginZ);

    //! Returns builder with initial value.
    [[nodiscard]] Builder& WithInitialValue(double initialValU,
                                            double initialValV,
                                            double initialValW);

    //! Builds VertexCenteredVectorGrid3 instance.
    [[nodiscard]] VertexCenteredVectorGrid3 Build() const;

    //! Builds shared pointer of VertexCenteredVectorGrid3 instance.
    [[nodiscard]] VertexCenteredVectorGrid3Ptr MakeShared() const;

    //!
    //! \brief Builds shared pointer of VertexCenteredVectorGrid3 instance.
    //!
    //! This is an overriding function that implements VectorGridBuilder3.
    //!
    [[nodiscard]] VectorGrid3Ptr Build(
        const Size3& resolution, const Vector3D& gridSpacing,
        const Vector3D& gridOrigin, const Vector3D& initialVal) const override;

 private:
    Size3 m_resolution{ 1, 1, 1 };
    Vector3D m_gridSpacing{ 1, 1, 1 };
    Vector3D m_gridOrigin{ 0, 0, 0 };
    Vector3D m_initialVal{ 0, 0, 0 };
};
}  // namespace CubbyFlow

#endif