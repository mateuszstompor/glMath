//
//  matrix3f.h
//  glMath
//
//  Created by Mateusz Stompór on 08/04/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#pragma once

#include "matrix.h"

namespace ms::math {
    template <>
    class Matrix<float, 3, 3> {
    public:
        //static functions
        inline static Matrix                diagonal            (float);
        inline static Matrix                identity            ();
    public:
                                            Matrix              () = default;
        inline                              Matrix              (float);
        inline                              Matrix              (const Matrix &);
        inline                              Matrix              (const float [9]);
        inline Matrix                       operator -          (const Matrix &) const;
        inline Matrix &                     operator -=         (const Matrix &);
        inline Matrix                       operator +          (const Matrix &) const;
        inline Matrix &                     operator +=         (const Matrix &);
        inline Matrix &                     operator *=         (const Matrix &);
        inline Matrix &                     operator =          (const Matrix &);
        template <std::uint8_t C>
        inline Matrix<float, 3, C>          operator *          (const Matrix<float, 3, C> &) const;
        inline Matrix<float, 3, 3>          operator *          (const Matrix<float, 3, 3> &) const;
        inline Vector<float, 3>             operator *          (const Vector<float, 3> &) const;
        inline Matrix &                     operator *=         (float);
        inline Matrix                       operator *          (float) const;
        inline bool                         operator ==         (const Matrix &) const;
        inline bool                         operator !=         (const Matrix &) const;
        inline constexpr float &            operator []         (std::uint8_t);
        inline constexpr const float &      operator []         (std::uint8_t) const;
        inline Matrix                       transposition       () const;
        inline std::string                  to_string           () const;
        inline constexpr float *            c_array             ();
        inline constexpr const float *      c_array             () const;
        float                               components[9];
    };
}

ms::math::Matrix<float, 3, 3> ms::math::Matrix<float, 3, 3> :: identity () {
    Matrix result;
    result.components[0] = 1.0f;
    result.components[1] = 0.0f;
    result.components[2] = 0.0f;
    result.components[3] = 0.0f;
    result.components[4] = 1.0f;
    result.components[5] = 0.0f;
    result.components[6] = 0.0f;
    result.components[7] = 0.0f;
    result.components[8] = 1.0f;
    return result;
}


ms::math::Matrix<float, 3, 3> ms::math::Matrix<float, 3, 3> :: diagonal (float value) {
    Matrix result;
    result.components[0] = value;
    result.components[1] = 0.0f;
    result.components[2] = 0.0f;
    result.components[3] = 0.0f;
    result.components[4] = value;
    result.components[5] = 0.0f;
    result.components[6] = 0.0f;
    result.components[7] = 0.0f;
    result.components[8] = value;
    return result;
}

ms::math::Matrix<float, 3, 3> :: Matrix(float value) {
    components[0] = value;
    components[1] = value;
    components[2] = value;
    components[3] = value;
    components[4] = value;
    components[5] = value;
    components[6] = value;
    components[7] = value;
    components[8] = value;
}

ms::math::Matrix<float, 3, 3> :: Matrix(const Matrix & m) {
    std::memcpy(components, m.components, sizeof(float) * 9);
}

ms::math::Matrix<float, 3, 3> :: Matrix(const float array [9]) {
    std::memcpy(components, array, sizeof(float) * 9);
}

ms::math::Matrix<float, 3, 3> ms::math::Matrix<float, 3, 3> :: operator - (const Matrix<float, 3, 3> & m) const {
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
    return result;
}

ms::math::Matrix<float, 3, 3> & ms::math::Matrix<float, 3, 3> :: operator -= (const Matrix<float, 3, 3> & m) {
    components[0] -= m.components[0];
    components[1] -= m.components[1];
    components[2] -= m.components[2];
    components[3] -= m.components[3];
    components[4] -= m.components[4];
    components[5] -= m.components[5];
    components[6] -= m.components[6];
    components[7] -= m.components[7];
    components[8] -= m.components[8];
    return *this;
}

ms::math::Matrix<float, 3, 3> ms::math::Matrix<float, 3, 3> :: operator + (const Matrix & m) const {
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
    return result;
}

ms::math::Matrix<float, 3, 3> & ms::math::Matrix<float, 3, 3> :: operator += (const Matrix & m) {
    components[0] += m.components[0];
    components[1] += m.components[1];
    components[2] += m.components[2];
    components[3] += m.components[3];
    components[4] += m.components[4];
    components[5] += m.components[5];
    components[6] += m.components[6];
    components[7] += m.components[7];
    components[8] += m.components[8];
    return *this;
}

ms::math::Matrix<float, 3, 3> & ms::math::Matrix<float, 3, 3> :: operator *= (const Matrix & m) {
    (*this) = (*this) * m;
    return (*this);
}

template <std::uint8_t C>
ms::math::Matrix<float, 3, C> ms::math::Matrix<float, 3, 3> :: operator * (const Matrix<float, 3, C> & m) const {
    Matrix <float, 3, C> result;
    for(std::uint8_t outerIterator = 0; outerIterator < 3; ++outerIterator)
        for (std::uint8_t innerIterator = 0; innerIterator < C; ++innerIterator) {
            result.components[3 * innerIterator + outerIterator] = 0;
            for (std::uint8_t i = 0; i < 3; ++i)
                result.components[3 * innerIterator + outerIterator] += components[3*i + outerIterator ] * m.components[3*innerIterator + i];
        }
    return result;
}

ms::math::Matrix<float, 3, 3> & ms::math::Matrix<float, 3, 3>::operator = (const Matrix & m) {
    std::memcpy(components, m.components, sizeof(float) * 9);
    return *this;
}

ms::math::Vector<float, 3> ms::math::Matrix<float, 3, 3> :: operator * (const Vector<float, 3> & v) const {
    return Vector<float, 3>(v.components[0] * components[0] +
                            v.components[1] * components[3] +
                            v.components[2] * components[6],
                            v.components[0] * components[1] +
                            v.components[1] * components[4] +
                            v.components[2] * components[7],
                            v.components[0] * components[2] +
                            v.components[1] * components[5] +
                            v.components[2] * components[8]);
}

ms::math::Matrix<float, 3, 3> & ms::math::Matrix<float, 3, 3> :: operator *= (float value) {
    components[0] *= value;
    components[1] *= value;
    components[2] *= value;
    components[3] *= value;
    components[4] *= value;
    components[5] *= value;
    components[6] *= value;
    components[7] *= value;
    components[8] *= value;
    return (*this);
}

ms::math::Matrix<float, 3, 3> ms::math::Matrix<float, 3, 3> :: operator * (float value) const {
    Matrix result;
    result.components[0] = components[0] * value;
    result.components[1] = components[1] * value;
    result.components[2] = components[2] * value;
    result.components[3] = components[3] * value;
    result.components[4] = components[4] * value;
    result.components[5] = components[5] * value;
    result.components[6] = components[6] * value;
    result.components[7] = components[7] * value;
    result.components[8] = components[8] * value;
    return result;
}

bool ms::math::Matrix<float, 3, 3> :: operator == (const Matrix & m) const {
    return !((*this) != m);
}

bool ms::math::Matrix<float, 3, 3> :: operator != (const Matrix & m) const {
    for(std::uint8_t i = 0; i < 9; ++i) {
        if (m.components[i] != components[i])
            return true;
    }
    return false;
}

ms::math::Matrix<float, 3, 3> ms::math::Matrix<float, 3, 3> :: transposition () const {
    Matrix mat;
    for (std::uint8_t row = 0; row < 3; ++row)
        for (std::uint8_t column = 0; column < 3; ++column)
            mat.components[row * 3 + column] = components[row + column * 3];
    return mat;
}

constexpr float & ms::math::Matrix<float, 3, 3> :: operator [] (std::uint8_t index) {
    return components[index];
}

constexpr const float & ms::math::Matrix<float, 3, 3> :: operator [] (std::uint8_t index) const {
    return components[index];
}

std::string ms::math::Matrix<float, 3, 3> :: to_string() const {
    std::ostringstream output;
    output << std::setprecision(2) << components[0] << " ";
    output << std::setprecision(2) << components[3] << " ";
    output << std::setprecision(2) << components[6] << "\n";
    output << std::setprecision(2) << components[1] << " ";
    output << std::setprecision(2) << components[4] << " ";
    output << std::setprecision(2) << components[7] << "\n";
    output << std::setprecision(2) << components[2] << " ";
    output << std::setprecision(2) << components[5] << " ";
    output << std::setprecision(2) << components[8] << "\n";
    return output.str();
}

constexpr const float * ms::math::Matrix<float, 3, 3> :: c_array() const {
    return components;
}

constexpr float * ms::math::Matrix<float, 3, 3> :: c_array() {
    return components;
}

ms::math::Matrix<float, 3, 3> ms::math::Matrix<float, 3, 3> ::operator * (const Matrix<float, 3, 3> & m) const {
    Matrix <float, 3, 3> result;
    result.components[0] =
    components[0 ] * m.components[0] +
    components[3] * m.components[1] +
    components[6] * m.components[2];
    result.components[3] =
    components[0] * m.components[3] +
    components[3] * m.components[4] +
    components[6] * m.components[5];
    result.components[6] =
    components[0] * m.components[6] +
    components[3] * m.components[7] +
    components[6] * m.components[8];
    result.components[1] =
    components[1] * m.components[0] +
    components[4] * m.components[1] +
    components[7] * m.components[2];
    result.components[4] =
    components[1] * m.components[3] +
    components[4] * m.components[4] +
    components[7] * m.components[5];
    result.components[7] =
    components[1] * m.components[6] +
    components[4] * m.components[7] +
    components[7] * m.components[8];
    result.components[2] =
    components[2] * m.components[0] +
    components[5] * m.components[1] +
    components[8] * m.components[2];
    result.components[5] =
    components[2] * m.components[3] +
    components[5] * m.components[4] +
    components[8] * m.components[5];
    result.components[8] =
    components[2] * m.components[6] +
    components[5] * m.components[7] +
    components[8] * m.components[8];
    return result;
}
