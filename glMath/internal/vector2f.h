//
//  vector2f.h
//  glMath
//
//  Created by Mateusz Stompór on 04/05/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#pragma once

#include "vector.h"

namespace ms::math {
    template<>
    class Vector<float, 2> {
    public:
                                            Vector              () = default;
        inline                              Vector              (const Vector & v);
        inline                              Vector              (const Vector<float, 1> & v, float value);
        inline                              Vector              (const float array [2]);
        inline                              Vector              (float x, float y);
                                            ~Vector             () = default;
        inline Vector &                     operator    =       (const Vector & v);
        inline bool                         operator    ==      (const Vector & v) const;
        inline bool                         operator    !=      (const Vector & v) const;
        inline Vector                       operator    +       (const Vector & v) const;
        inline Vector &                     operator    +=      (const Vector & v);
        inline Vector                       operator    -       (const Vector & v) const;
        inline Vector &                     operator    -=      (const Vector & v);
        inline Vector                       operator    -       () const;
        inline Vector                       operator    /       (float value) const;
        inline Vector&                      operator    /=      (float value);
        inline Vector                       operator    *       (float value) const;
        inline Vector&                      operator    *=      (float value);
        template <std::uint8_t Columns>
        Vector<float, Columns>              operator    *       (const Matrix<float, 2, Columns> &) const;
        template <std::uint8_t Columns>
        inline Vector<float, Columns> &     operator    *=      (const Matrix<float, 2, Columns> &);
        inline constexpr float &            operator    []      (size_t position);
        inline constexpr float const &      operator    []      (size_t position) const;
        inline float                        dot                 (const Vector & v) const;
        inline float                        length              () const;
        inline float                        length2             () const;
        inline Vector &                     normalize           ();
        inline Vector                       normalized          () const;
        inline std::string                  to_string           () const;
        inline constexpr float *            c_array             ();
        inline constexpr const float *      c_array             () const;
        inline constexpr float const &      x                   () const;
        inline constexpr float &            x                   ();
        inline constexpr float const &      y                   () const;
        inline constexpr float &            y                   ();
        float                               components [2];
    };
}

ms::math::Vector<float, 2>::Vector(const Vector & v) {
    std::memcpy(components, v.components, 2 * sizeof(float));
}

ms::math::Vector<float, 2>::Vector (const Vector<float, 1> & v, float value) {
    std::memcpy(components, v.components, sizeof(float));
    components[1] = value;
}

ms::math::Vector<float, 2>::Vector(const float array [2]) : Vector() {
    std::memcpy(components, array, 2 * sizeof(float));
}

ms::math::Vector<float, 2>::Vector (float x, float y) : components{x, y} { }

ms::math::Vector<float, 2> & ms::math::Vector<float, 2>::operator = (const Vector & v) {
    std::memcpy(components, v.components, 2 * sizeof(float));
    return *this;
}

bool ms::math::Vector<float, 2>::operator == (const Vector & v) const {
    return  v.components[0] == components[0] &&
            v.components[1] == components[1];
}

bool ms::math::Vector<float, 2>::operator != (const Vector & v) const {
    return  v.components[0] != components[0] ||
            v.components[1] != components[1];
}

float ms::math::Vector<float, 2>::dot(const Vector & v) const {
    return  components[0] * v.components[0] +
            components[1] * v.components[1];
}

ms::math::Vector<float, 2> & ms::math::Vector<float, 2>::operator /= (float value) {
    components[0] /= value;
    components[1] /= value;
    return *this;
}

ms::math::Vector<float, 2> ms::math::Vector<float, 2>::operator / (float value) const {
    return Vector(components[0] / value, components[1] / value);
}

ms::math::Vector<float, 2> & ms::math::Vector<float, 2>::operator *= (float value) {
    components[0] *= value;
    components[1] *= value;
    return *this;
}

ms::math::Vector<float, 2> ms::math::Vector<float, 2>::operator * (float value) const {
    return Vector(components[0] * value, components[1] * value);
}

template <std::uint8_t Columns>
ms::math::Vector<float, Columns> ms::math::Vector<float, 2> :: operator * (const Matrix<float, 2, Columns> & m) const {
    Vector<float, Columns> result;
    for(std::uint8_t row = 0; row < 2; ++row) {
        result.components[row] = 0.0f;
        for(std::uint8_t column = 0; column < Columns; ++column)
            result.components[row] += components[column] * m.components[2 * column + row];
    }
    return result;
}

template <std::uint8_t Columns>
ms::math::Vector<float, Columns> & ms::math::Vector<float, 2> :: operator *= (const Matrix<float, 2, Columns> & m) {
    Vector<float, Columns> result = (*this) * m;
    *this = result;
    return *this;
}

ms::math::Vector<float, 2> ms::math::Vector<float, 2> :: operator - () const {
    return Vector(-components[0], -components[1]);
}

constexpr float& ms::math::Vector<float, 2>::operator [] (size_t position) {
    return components[position];
}

constexpr const float& ms::math::Vector<float, 2>::operator [] (size_t position) const {
    return components[position];
}

ms::math::Vector<float, 2> ms::math::Vector<float, 2>::operator + (const Vector & v) const {
    return ms::math::Vector<float, 2>(v.components[0] + components[0],
                                      v.components[1] + components[1]);
}

ms::math::Vector<float, 2> ms::math::Vector<float, 2>::operator - (const Vector & v) const {
    return ms::math::Vector<float, 2>(components[0] - v.components[0],
                                      components[1] - v.components[1]);
}

ms::math::Vector<float, 2> & ms::math::Vector<float, 2>::operator += (const Vector & v) {
    components[0] += v.components[0];
    components[1] += v.components[1];
    return *this;
}

ms::math::Vector<float, 2> & ms::math::Vector<float, 2>::operator -= (const Vector & v) {
    components[0] -= v.components[0];
    components[1] -= v.components[1];
    return *this;
}

float ms::math::Vector<float, 2>::length() const {
    return std::sqrt(components[0] * components[0] + components[1] * components[1]);
}

float ms::math::Vector<float, 2>::length2() const {
    return components[0] * components[0] + components[1] * components[1];
}

ms::math::Vector<float, 2> & ms::math::Vector<float, 2>::normalize() {
    float len = std::sqrt(components[0] * components[0] + components[1] * components[1]);
    components[0] /= len;
    components[1] /= len;
    return *this;
}

ms::math::Vector<float, 2> ms::math::Vector<float, 2> :: normalized() const {
    float len = std::sqrt(components[0] * components[0] + components[1] * components[1]);
    return Vector(components[0]/len, components[1]/len);
}

std::string ms::math::Vector<float, 2>::to_string() const {
    std::ostringstream output;
    output << components[0] << ' ';
    output << components[1] << '\n';
    return output.str();
}

constexpr const float * ms::math::Vector<float, 2>::c_array() const {
    return components;
}

constexpr float * ms::math::Vector<float, 2>::c_array() {
    return components;
}

constexpr float const & ms::math::Vector <float, 2>::x () const {
    return *components;
}

constexpr float & ms::math::Vector <float, 2>::x () {
    return *components;
}

constexpr float const & ms::math::Vector <float, 2>::y () const {
    return *(components + 1);
}

constexpr float & ms::math::Vector <float, 2>::y () {
    return *(components + 1);
}

