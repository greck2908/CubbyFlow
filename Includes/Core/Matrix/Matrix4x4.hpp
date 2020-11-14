// This code is based on Jet framework.
// Copyright (c) 2018 Doyub Kim
// CubbyFlow is voxel-based fluid simulation engine for computer games.
// Copyright (c) 2020 CubbyFlow Team
// Core Part: Chris Ohk, Junwoo Hwang, Jihong Sin, Seungwoo Yoo
// AI Part: Dongheon Cho, Minseo Kim
// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef CUBBYFLOW_MATRIX4X4_HPP
#define CUBBYFLOW_MATRIX4X4_HPP

#include <Core/Matrix/Matrix3x3.hpp>
#include <Core/Vector/Vector4.hpp>

#include <array>
#include <limits>

namespace CubbyFlow
{
//!
//! \brief 4-D matrix class.
//!
//! This class is a row-major 4-D matrix class, which means each element of
//! the matrix is stored in order of (0,0), ... , (0,3), (1,0), ... , (3,3).
//! Also, this 4-D matrix is specialized for geometric transformations.
//! \tparam T - Type of the element.
//!
template <typename T>
class Matrix<T, 4, 4>
{
 public:
    static_assert(std::is_floating_point<T>::value,
                  "Matrix only can be instantiated with floating point types");

    //! Constructs identity matrix.
    Matrix();

    //! Constructs constant value matrix.
    explicit Matrix(T s);

    //! Constructs a matrix with input elements.
    //! This constructor initialize 3x3 part, and other parts are set to 0
    //! except (3,3) which will be set to 1.
    //! \warning Ordering of the input elements is row-major.
    Matrix(T m00, T m01, T m02, T m10, T m11, T m12, T m20, T m21, T m22);

    //! Constructs a matrix with input elements.
    //! \warning Ordering of the input elements is row-major.
    Matrix(T m00, T m01, T m02, T m03, T m10, T m11, T m12, T m13, T m20, T m21,
           T m22, T m23, T m30, T m31, T m32, T m33);

    //!
    //! \brief Constructs a matrix with given initializer list \p list.
    //!
    //! This constructor will build a matrix with given initializer list \p list
    //! such as
    //!
    //! \code{.cpp}
    //! Matrix<float, 4, 4> arr =
    //! {
    //!     {1.f, 2.f, 4.f, 3.f},
    //!     {9.f, 3.f, 5.f, 1.f},
    //!     {4.f, 8.f, 1.f, 5.f},
    //!     {3.f, 7.f, 2.f, 6.f}
    //! };
    //! \endcode
    //!
    //! Note the initializer also has 4x4 structure.
    //!
    //! \param list Initializer list that should be copy to the new matrix.
    //!
    template <typename U>
    Matrix(const std::initializer_list<std::initializer_list<U>>& list);

    //! Constructs a matrix with 3x3 matrix.
    //! This constructor initialize 3x3 part, and other parts are set to 0
    //! except (3,3) which is set to 1.
    explicit Matrix(const Matrix3x3<T>& m33);

    //! Constructs a matrix with input array.
    //! \warning Ordering of the input elements is row-major.
    explicit Matrix(const T* arr);

    //! Copy constructor.
    Matrix(const Matrix& m);

    //! Default move constructor.
    Matrix(Matrix&&) noexcept = default;

    //! Default destructor.
    ~Matrix() = default;

    //! Copy assignment operator.
    Matrix& operator=(const Matrix& m);

    //! Default move assignment operator.
    Matrix& operator=(Matrix&&) noexcept = default;

    //! Sets whole matrix with input scalar.
    void Set(T s);

    //! Sets this matrix with input elements.
    //! This method copies 3x3 part only, and other parts are set to 0
    //! except (3,3) which is set to 1.
    //! \warning Ordering of the input elements is row-major.
    void Set(T m00, T m01, T m02, T m10, T m11, T m12, T m20, T m21, T m22);

    //! Sets this matrix with input elements.
    //! \warning Ordering of the input elements is row-major.
    void Set(T m00, T m01, T m02, T m03, T m10, T m11, T m12, T m13, T m20,
             T m21, T m22, T m23, T m30, T m31, T m32, T m33);

    //!
    //! \brief Sets a matrix with given initializer list \p list.
    //!
    //! This function will fill the matrix with given initializer list \p list
    //! such as
    //!
    //! \code{.cpp}
    //! Matrix<float, 4, 4> arr;
    //! arr.Set(
    //! {
    //!     {1.f, 2.f, 4.f, 3.f},
    //!     {9.f, 3.f, 5.f, 1.f},
    //!     {4.f, 8.f, 1.f, 5.f},
    //!     {3.f, 7.f, 2.f, 6.f}
    //! });
    //! \endcode
    //!
    //! Note the initializer also has 3x3 structure.
    //!
    //! \param list Initializer list that should be copy to the new matrix.
    //!
    template <typename U>
    void Set(const std::initializer_list<std::initializer_list<U>>& list);

    //! Sets this matrix with input 3x3 matrix.
    //! This method copies 3x3 part only, and other parts are set to 0
    //! except (3,3) which will be set to 1.
    void Set(const Matrix<T, 3, 3>& m33);

    //! Copies from input matrix.
    void Set(const Matrix& m);

    //! Copies from input array.
    //! \warning Ordering of the input elements is row-major.
    void Set(const T* arr);

    //! Sets diagonal elements with input scalar.
    void SetDiagonal(T s);

    //! Sets off-diagonal elements with input scalar.
    void SetOffDiagonal(T s);

    //! Sets i-th row with input vector.
    void SetRow(size_t i, const Vector4<T>& row);

    //! Sets i-th column with input vector.
    void SetColumn(size_t i, const Vector4<T>& col);

    //! Returns true if this matrix is similar to the input matrix within the
    //! given tolerance.
    [[nodiscard]] bool IsSimilar(
        const Matrix& m,
        double tol = std::numeric_limits<double>::epsilon()) const;

    //! Returns true if this matrix is a square matrix.
    [[nodiscard]] static bool IsSquare();

    //! Returns number of rows of this matrix.
    [[nodiscard]] static size_t Rows();

    //! Returns number of columns of this matrix.
    [[nodiscard]] static size_t Cols();

    //! Returns data pointer of this matrix.
    [[nodiscard]] T* data();

    //! Returns constant pointer of this matrix.
    [[nodiscard]] const T* data() const;

    //! Returns 3x3 part of this matrix.
    [[nodiscard]] Matrix<T, 3, 3> Matrix3() const;

    //! Returns this matrix + input scalar.
    [[nodiscard]] Matrix Add(T s) const;

    //! Returns this matrix + input matrix (element-wise).
    [[nodiscard]] Matrix Add(const Matrix& m) const;

    //! Returns this matrix - input scalar.
    [[nodiscard]] Matrix Sub(T s) const;

    //! Returns this matrix - input matrix (element-wise).
    [[nodiscard]] Matrix Sub(const Matrix& m) const;

    //! Returns this matrix * input scalar.
    [[nodiscard]] Matrix Mul(T s) const;

    //! Returns this matrix * input vector.
    [[nodiscard]] Vector4<T> Mul(const Vector4<T>& v) const;

    //! Returns this matrix * input matrix.
    [[nodiscard]] Matrix Mul(const Matrix& m) const;

    //! Returns this matrix / input scalar.
    [[nodiscard]] Matrix Div(T s) const;

    //! Returns input scalar + this matrix.
    [[nodiscard]] Matrix RAdd(T s) const;

    //! Returns input matrix + this matrix (element-wise).
    [[nodiscard]] Matrix RAdd(const Matrix& m) const;

    //! Returns input scalar - this matrix.
    [[nodiscard]] Matrix RSub(T s) const;

    //! Returns input matrix - this matrix (element-wise).
    [[nodiscard]] Matrix RSub(const Matrix& m) const;

    //! Returns input scalar * this matrix.
    [[nodiscard]] Matrix RMul(T s) const;

    //! Returns input matrix * this matrix.
    [[nodiscard]] Matrix RMul(const Matrix& m) const;

    //! Returns input matrix / this scalar.
    [[nodiscard]] Matrix RDiv(T s) const;

    //! Adds input scalar to this matrix.
    void IAdd(T s);

    //! Adds input matrix to this matrix (element-wise).
    void IAdd(const Matrix& m);

    //! Subtracts input scalar from this matrix.
    void ISub(T s);

    //! Subtracts input matrix from this matrix (element-wise).
    void ISub(const Matrix& m);

    //! Multiplies input scalar to this matrix.
    void IMul(T s);

    //! Multiplies input matrix to this matrix.
    void IMul(const Matrix& m);

    //! Divides this matrix with input scalar.
    void IDiv(T s);

    //! Transposes this matrix.
    void Transpose();

    //! Inverts this matrix.
    void Invert();

    //! Returns sum of all elements.
    [[nodiscard]] T Sum() const;

    //! Returns average of all elements.
    [[nodiscard]] T Avg() const;

    //! Returns minimum among all elements.
    [[nodiscard]] T Min() const;

    //! Returns maximum among all elements.
    [[nodiscard]] T Max() const;

    //! Returns absolute minimum among all elements.
    [[nodiscard]] T AbsMin() const;

    //! Returns absolute maximum among all elements.
    [[nodiscard]] T AbsMax() const;

    //! Returns sum of all diagonal elements.
    [[nodiscard]] T Trace() const;

    //! Returns determinant of this matrix.
    [[nodiscard]] T Determinant() const;

    //! Returns diagonal part of this matrix.
    [[nodiscard]] Matrix Diagonal() const;

    //! Returns off-diagonal part of this matrix.
    [[nodiscard]] Matrix OffDiagonal() const;

    //! Returns strictly lower triangle part of this matrix.
    [[nodiscard]] Matrix StrictLowerTriangle() const;

    //! Returns strictly upper triangle part of this matrix.
    [[nodiscard]] Matrix StrictUpperTriangle() const;

    //! Returns lower triangle part of this matrix (including the diagonal).
    [[nodiscard]] Matrix LowerTriangle() const;

    //! Returns upper triangle part of this matrix (including the diagonal).
    [[nodiscard]] Matrix UpperTriangle() const;

    //! Returns transposed matrix.
    [[nodiscard]] Matrix Transposed() const;

    //! Returns inverse matrix.
    [[nodiscard]] Matrix Inverse() const;

    template <typename U>
    [[nodiscard]] Matrix<U, 4, 4> CastTo() const;

    //! Addition assignment with input scalar.
    Matrix& operator+=(T s);

    //! Addition assignment with input matrix (element-wise).
    Matrix& operator+=(const Matrix& m);

    //! Subtraction assignment with input scalar.
    Matrix& operator-=(T s);

    //! Subtraction assignment with input matrix (element-wise).
    Matrix& operator-=(const Matrix& m);

    //! Multiplication assignment with input scalar.
    Matrix& operator*=(T s);

    //! Multiplication assignment with input matrix.
    Matrix& operator*=(const Matrix& m);

    //! Division assignment with input scalar.
    Matrix& operator/=(T s);

    //! Returns reference of i-th element.
    T& operator[](size_t i);

    //! Returns constant reference of i-th element.
    const T& operator[](size_t i) const;

    //! Returns reference of (i,j) element.
    T& operator()(size_t i, size_t j);

    //! Returns constant reference of (i,j) element.
    const T& operator()(size_t i, size_t j) const;

    //! Returns true if is equal to m.
    bool operator==(const Matrix& m) const;

    //! Returns true if is not equal to m.
    bool operator!=(const Matrix& m) const;

    //! Sets all matrix entries to zero.
    [[nodiscard]] static Matrix MakeZero();

    //! Makes all diagonal elements to 1, and other elements to 0.
    [[nodiscard]] static Matrix MakeIdentity();

    //! Makes scale matrix.
    [[nodiscard]] static Matrix MakeScaleMatrix(T sx, T sy, T sz);

    //! Makes scale matrix.
    [[nodiscard]] static Matrix MakeScaleMatrix(const Vector3<T>& s);

    //! Makes rotation matrix.
    //! \warning Input angle should be radian.
    [[nodiscard]] static Matrix MakeRotationMatrix(const Vector3<T>& axis,
                                                   T rad);

    //! Makes translation matrix.
    [[nodiscard]] static Matrix MakeTranslationMatrix(const Vector3<T>& t);

 private:
    std::array<T, 16> m_elements;
};

//! Type alias for 4x4 matrix.
template <typename T>
using Matrix4x4 = Matrix<T, 4, 4>;

// Operator overloading
//! Returns a matrix with opposite sign.
template <typename T>
Matrix<T, 4, 4> operator-(const Matrix<T, 4, 4>& a);

//! Returns a + b (element-size).
template <typename T>
Matrix<T, 4, 4> operator+(const Matrix<T, 4, 4>& a, const Matrix<T, 4, 4>& b);

//! Returns a + b', where every element of matrix b' is b.
template <typename T>
Matrix<T, 4, 4> operator+(const Matrix<T, 4, 4>& a, T b);

//! Returns a' + b, where every element of matrix a' is a.
template <typename T>
Matrix<T, 4, 4> operator+(T a, const Matrix<T, 4, 4>& b);

//! Returns a - b (element-size).
template <typename T>
Matrix<T, 4, 4> operator-(const Matrix<T, 4, 4>& a, const Matrix<T, 4, 4>& b);

//! Returns a - b', where every element of matrix b' is b.
template <typename T>
Matrix<T, 4, 4> operator-(const Matrix<T, 4, 4>& a, T b);

//! Returns a' - b, where every element of matrix a' is a.
template <typename T>
Matrix<T, 4, 4> operator-(T a, const Matrix<T, 4, 4>& b);

//! Returns a * b', where every element of matrix b' is b.
template <typename T>
Matrix<T, 4, 4> operator*(const Matrix<T, 4, 4>& a, T b);

//! Returns a' * b, where every element of matrix a' is a.
template <typename T>
Matrix<T, 4, 4> operator*(T a, const Matrix<T, 4, 4>& b);

//! Returns a * b.
template <typename T>
Vector3<T> operator*(const Matrix<T, 4, 4>& a, const Vector3<T>& b);

//! Returns a * b.
template <typename T>
Vector4<T> operator*(const Matrix<T, 4, 4>& a, const Vector4<T>& b);

//! Returns a * b.
template <typename T>
Matrix<T, 4, 4> operator*(const Matrix<T, 4, 4>& a, const Matrix<T, 4, 4>& b);

//! Returns a' / b, where every element of matrix a' is a.
template <typename T>
Matrix<T, 4, 4> operator/(const Matrix<T, 4, 4>& a, T b);

//! Returns a / b', where every element of matrix b' is b.
template <typename T>
Matrix<T, 4, 4> operator/(const T& a, const Matrix<T, 4, 4>& b);

//! Float-type 4x4 matrix.
using Matrix4x4F = Matrix4x4<float>;

//! Double-type 4x4 matrix.
using Matrix4x4D = Matrix4x4<double>;
}  // namespace CubbyFlow

#include <Core/Matrix/Matrix4x4-Impl.hpp>

#endif