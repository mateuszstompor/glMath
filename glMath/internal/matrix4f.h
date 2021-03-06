//
//  matrix4f.h
//  glMath
//
//  Created by Mateusz Stompór on 06/04/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#pragma once

#include "matrix.h"

namespace ms::math {
    template <>
    class Matrix<float, 4, 4> {
    public:
        inline static Matrix                diagonal            (float value);
        inline static Matrix                identity            ();
    public:
                                            Matrix              () = default;
        inline                              Matrix              (float value);
        inline                              Matrix              (const Matrix & m);
        inline                              Matrix              (const float array [16]);
        inline Matrix                       operator -          (const Matrix & m) const;
        inline Matrix &                     operator -=         (const Matrix & m);
        inline Matrix                       operator +          (const Matrix & m) const;
        inline Matrix &                     operator +=         (const Matrix & m);
        inline Matrix &                     operator *=         (const Matrix & m);
        inline Matrix &                     operator =          (const Matrix & m);
        template <std::uint8_t C>
        inline Matrix<float, 4, C>          operator *          (const Matrix<float, 4, C> &) const;
        inline Matrix<float, 4, 4>          operator *          (const Matrix<float, 4, 4> & m) const;
        inline Vector<float, 4>             operator *          (const Vector<float, 4> & b) const;
        inline Matrix &                     operator *=         (float value);
        inline Matrix                       operator *          (float value) const;
        inline bool                         operator ==         (const Matrix & m) const;
        inline bool                         operator !=         (const Matrix & m) const;
        inline constexpr float &            operator []         (std::uint8_t index);
        inline constexpr const float &      operator []         (std::uint8_t index) const;
        inline Matrix                       transposition       () const;
        inline std::string                  to_string           () const;
        inline constexpr float *            c_array             ();
        inline constexpr const float *      c_array             () const;
        float                               components[16];

    };
}

ms::math::Matrix<float, 4, 4> ms::math::Matrix<float, 4, 4> :: identity () {
    Matrix result;
    result.components[0] = 1.0f;
    result.components[1] = 0.0f;
    result.components[2] = 0.0f;
    result.components[3] = 0.0f;
    result.components[4] = 0.0f;
    result.components[5] = 1.0f;
    result.components[6] = 0.0f;
    result.components[7] = 0.0f;
    result.components[8] = 0.0f;
    result.components[9] = 0.0f;
    result.components[10] = 1.0f;
    result.components[11] = 0.0f;
    result.components[12] = 0.0f;
    result.components[13] = 0.0f;
    result.components[14] = 0.0f;
    result.components[15] = 1.0f;
    return result;
}


ms::math::Matrix<float, 4, 4> ms::math::Matrix<float, 4, 4> :: diagonal (float value) {
    Matrix result;
    result.components[0] = value;
    result.components[1] = 0.0f;
    result.components[2] = 0.0f;
    result.components[3] = 0.0f;
    result.components[4] = 0.0f;
    result.components[5] = value;
    result.components[6] = 0.0f;
    result.components[7] = 0.0f;
    result.components[8] = 0.0f;
    result.components[9] = 0.0f;
    result.components[10] = value;
    result.components[11] = 0.0f;
    result.components[12] = 0.0f;
    result.components[13] = 0.0f;
    result.components[14] = 0.0f;
    result.components[15] = value;
    return result;
}

ms::math::Matrix<float, 4, 4> :: Matrix(float value) {
    components[0] = value;
    components[1] = value;
    components[2] = value;
    components[3] = value;
    components[4] = value;
    components[5] = value;
    components[6] = value;
    components[7] = value;
    components[8] = value;
    components[9] = value;
    components[10] = value;
    components[11] = value;
    components[12] = value;
    components[13] = value;
    components[14] = value;
    components[15] = value;
}

ms::math::Matrix<float, 4, 4> :: Matrix(const Matrix & m) {
    std::memcpy(components, m.components, sizeof(float) * 16);
}

ms::math::Matrix<float, 4, 4> :: Matrix(const float array [16]) {
    std::memcpy(components, array, sizeof(float) * 16);
}

ms::math::Matrix<float, 4, 4> ms::math::Matrix<float, 4, 4> :: operator - (const Matrix<float, 4, 4> & m) const {
    Matrix result;
    result.components[0] = components[0] - m.components[0];
    result.components[1] = components[1] - m.components[1];
    result.components[2] = components[2] - m.components[2];
    result.components[3] = components[3] - m.components[3];
    result.components[4] = components[4] - m.components[4];
    result.components[5] = components[5] - m.components[5];
    result.components[6] = components[6] - m.components[6];
    result.components[7] = components[7] - m.components[7];
    result.components[8] = components[8] - m.components[8];
    result.components[9] = components[9] - m.components[9];
    result.components[10] = components[10] - m.components[10];
    result.components[11] = components[11] - m.components[11];
    result.components[12] = components[12] - m.components[12];
    result.components[13] = components[13] - m.components[13];
    result.components[14] = components[14] - m.components[14];
    result.components[15] = components[15] - m.components[15];
    return result;
}

ms::math::Matrix<float, 4, 4> & ms::math::Matrix<float, 4, 4>::operator = (const Matrix & m) {
    std::memcpy(components, m.components, sizeof(float) * 16);
    return *this;
}

ms::math::Matrix<float, 4, 4> & ms::math::Matrix<float, 4, 4> :: operator -= (const Matrix<float, 4, 4> & m) {
    components[0] -= m.components[0];
    components[1] -= m.components[1];
    components[2] -= m.components[2];
    components[3] -= m.components[3];
    components[4] -= m.components[4];
    components[5] -= m.components[5];
    components[6] -= m.components[6];
    components[7] -= m.components[7];
    components[8] -= m.components[8];
    components[9] -= m.components[9];
    components[10] -= m.components[10];
    components[11] -= m.components[11];
    components[12] -= m.components[12];
    components[13] -= m.components[13];
    components[14] -= m.components[14];
    components[15] -= m.components[15];
    return *this;
}

ms::math::Matrix<float, 4, 4> ms::math::Matrix<float, 4, 4> :: operator + (const Matrix & m) const {
    Matrix result;
    result.components[0] = components[0] + m.components[0];
    result.components[1] = components[1] + m.components[1];
    result.components[2] = components[2] + m.components[2];
    result.components[3] = components[3] + m.components[3];
    result.components[4] = components[4] + m.components[4];
    result.components[5] = components[5] + m.components[5];
    result.components[6] = components[6] + m.components[6];
    result.components[7] = components[7] + m.components[7];
    result.components[8] = components[8] + m.components[8];
    result.components[9] = components[9] + m.components[9];
    result.components[10] = components[10] + m.components[10];
    result.components[11] = components[11] + m.components[11];
    result.components[12] = components[12] + m.components[12];
    result.components[13] = components[13] + m.components[13];
    result.components[14] = components[14] + m.components[14];
    result.components[15] = components[15] + m.components[15];
    return result;
}

ms::math::Matrix<float, 4, 4> & ms::math::Matrix<float, 4, 4> :: operator += (const Matrix & m) {
    components[0] += m.components[0];
    components[1] += m.components[1];
    components[2] += m.components[2];
    components[3] += m.components[3];
    components[4] += m.components[4];
    components[5] += m.components[5];
    components[6] += m.components[6];
    components[7] += m.components[7];
    components[8] += m.components[8];
    components[9] += m.components[9];
    components[10] += m.components[10];
    components[11] += m.components[11];
    components[12] += m.components[12];
    components[13] += m.components[13];
    components[14] += m.components[14];
    components[15] += m.components[15];
    return *this;
}

ms::math::Matrix<float, 4, 4> & ms::math::Matrix<float, 4, 4> :: operator *= (const Matrix & m) {
    (*this) = (*this) * m;
    return (*this);
}

template <std::uint8_t C>
ms::math::Matrix<float, 4, C> ms::math::Matrix<float, 4, 4> :: operator * (const Matrix<float, 4, C> & m) const {
    Matrix <float, 4, C> result;
    for(std::uint8_t outerIterator = 0; outerIterator < 4; ++outerIterator)
        for (std::uint8_t innerIterator = 0; innerIterator < C; ++innerIterator) {
            result.components[4 * innerIterator + outerIterator] = 0;
            for (std::uint8_t i = 0; i < 4; ++i)
                result.components[4 * innerIterator + outerIterator] += components[4*i + outerIterator ] * m.components[4*innerIterator + i];
        }
    return result;
}

ms::math::Vector<float, 4> ms::math::Matrix<float, 4, 4> :: operator * (const Vector<float, 4> & v) const {
    Vector<float, 4> result;
    result.components[0] =
    v.components[0] * components[0] +
    v.components[1] * components[4] +
    v.components[2] * components[8] +
    v.components[3] * components[12];
    result.components[1] =
    v.components[0] * components[1] +
    v.components[1] * components[5] +
    v.components[2] * components[9] +
    v.components[3] * components[13];
    result.components[2] =
    v.components[0] * components[2] +
    v.components[1] * components[6] +
    v.components[2] * components[10] +
    v.components[3] * components[14];
    result.components[3] =
    v.components[0] * components[3] +
    v.components[1] * components[7] +
    v.components[2] * components[11] +
    v.components[3] * components[15];
    return result;
}

ms::math::Matrix<float, 4, 4> & ms::math::Matrix<float, 4, 4> :: operator *= (float value) {
    components[0] *= value;
    components[1] *= value;
    components[2] *= value;
    components[3] *= value;
    components[4] *= value;
    components[5] *= value;
    components[6] *= value;
    components[7] *= value;
    components[8] *= value;
    components[9] *= value;
    components[10] *= value;
    components[11] *= value;
    components[12] *= value;
    components[13] *= value;
    components[14] *= value;
    components[15] *= value;
    return (*this);
}

ms::math::Matrix<float, 4, 4> ms::math::Matrix<float, 4, 4> :: operator * (float value) const {
    Matrix result;
    result.components[0]    = components[0] * value;
    result.components[1]    = components[1] * value;
    result.components[2]    = components[2] * value;
    result.components[3]    = components[3] * value;
    result.components[4]    = components[4] * value;
    result.components[5]    = components[5] * value;
    result.components[6]    = components[6] * value;
    result.components[7]    = components[7] * value;
    result.components[8]    = components[8] * value;
    result.components[9]    = components[9] * value;
    result.components[10]   = components[10] * value;
    result.components[11]   = components[11] * value;
    result.components[12]   = components[12] * value;
    result.components[13]   = components[13] * value;
    result.components[14]   = components[14] * value;
    result.components[15]   = components[15] * value;
    return result;
}

bool ms::math::Matrix<float, 4, 4> :: operator == (const Matrix & m) const {
    return std::equal(std::begin(components), std::end(components), std::begin(m.components));
}

bool ms::math::Matrix<float, 4, 4> :: operator != (const Matrix & m) const {
    return !((*this) == m);
}

ms::math::Matrix<float, 4, 4> ms::math::Matrix<float, 4, 4> :: transposition () const {
    Matrix mat;
    for (std::uint8_t row = 0; row < 4; ++row)
        for (std::uint8_t column = 0; column < 4; ++column)
            mat.components[row * 4 + column] = components[row + column * 4];
    return mat;
}

constexpr float & ms::math::Matrix<float, 4, 4> :: operator [] (std::uint8_t index) {
    return components[index];
}

constexpr const float & ms::math::Matrix<float, 4, 4> :: operator [] (std::uint8_t index) const {
    return components[index];
}

std::string ms::math::Matrix<float, 4, 4> :: to_string() const {
    std::ostringstream output;
    for (std::uint8_t row = 0; row < 4; ++row) {
        for (std::uint8_t column = 0; column < 4; ++column) {
            output << std::setprecision(2) << components[column * 4 + row] << " ";
        }
        output << '\n';
    }
    return output.str();
}

constexpr const float * ms::math::Matrix<float, 4, 4> :: c_array() const {
    return components;
}

constexpr float * ms::math::Matrix<float, 4, 4> :: c_array() {
    return components;
}

ms::math::Matrix<float, 4, 4> ms::math::Matrix<float, 4, 4> ::operator * (const Matrix<float, 4, 4> & m) const {
    Matrix <float, 4, 4> result{};
    result.components[0] =
    components[0] * m.components[0] +
    components[4] * m.components[1] +
    components[8] * m.components[2] +
    components[12] * m.components[3];
    result.components[4] =
    components[0] * m.components[4] +
    components[4] * m.components[5] +
    components[8] * m.components[6] +
    components[12] * m.components[7];
    result.components[8] =
    components[0] * m.components[8] +
    components[4] * m.components[9] +
    components[8] * m.components[10] +
    components[12] * m.components[11];
    result.components[12] =
    components[0] * m.components[12] +
    components[4] * m.components[13] +
    components[8] * m.components[14] +
    components[12] * m.components[15];
    result.components[1] =
    components[1] * m.components[0] +
    components[5] * m.components[1] +
    components[9] * m.components[2] +
    components[13] * m.components[3];
    result.components[5] =
    components[1] * m.components[4] +
    components[5] * m.components[5] +
    components[9] * m.components[6] +
    components[13] * m.components[7];
    result.components[9] =
    components[1] * m.components[8] +
    components[5] * m.components[9] +
    components[9] * m.components[10] +
    components[13] * m.components[11];
    result.components[13] =
    components[1] * m.components[12] +
    components[5] * m.components[13] +
    components[9] * m.components[14] +
    components[13] * m.components[15];
    result.components[2] =
    components[2] * m.components[0] +
    components[6] * m.components[1] +
    components[10] * m.components[2] +
    components[14] * m.components[3];
    result.components[6] =
    components[2] * m.components[4] +
    components[6] * m.components[5] +
    components[10] * m.components[6] +
    components[14] * m.components[7];
    result.components[10] =
    components[2] * m.components[8] +
    components[6] * m.components[9] +
    components[10] * m.components[10] +
    components[14] * m.components[11];
    result.components[14] =
    components[2] * m.components[12] +
    components[6] * m.components[13] +
    components[10] * m.components[14] +
    components[14] * m.components[15];
    result.components[3] =
    components[3] * m.components[0] +
    components[7] * m.components[1] +
    components[11] * m.components[2] +
    components[15] * m.components[3];
    result.components[7] =
    components[3] * m.components[4] +
    components[7] * m.components[5] +
    components[11] * m.components[6] +
    components[15] * m.components[7];
    result.components[11] =
    components[3] * m.components[8] +
    components[7] * m.components[9] +
    components[11] * m.components[10] +
    components[15] * m.components[11];
    result.components[15] =
    components[3] * m.components[12] +
    components[7] * m.components[13] +
    components[11] * m.components[14] +
    components[15] * m.components[15];
    return result;
}
