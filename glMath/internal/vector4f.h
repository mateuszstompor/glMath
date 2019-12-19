//
//  vector4f.h
//  glMath
//
//  Created by Mateusz Stompór on 08/04/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#pragma once

#include "vector.h"

namespace ms::math {
    template<>
    class Vector<float, 4> {
    public:
                                            Vector              () = default;
        inline                              Vector              (const Vector & v);
        inline                              Vector              (const Vector<float, 3> & v, float value);
        inline                              Vector              (const float array [4]);
        inline                              Vector              (float x, float y, float z, float w);
        inline                              Vector              (const spco::RadiansSpherical<float> & sphericalCoordinates);
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
        inline Vector &                     operator    /=      (float value);
        inline Vector                       operator    *       (float value) const;
        inline Vector &                     operator    *=      (float value);
        inline Vector<float, 5>             expanded            (float value) const;
        template <std::uint8_t Columns>
        Vector<float, Columns>              operator    *       (const Matrix<float, 4, Columns> &) const;
        template <std::uint8_t Columns>
        inline Vector<float, Columns> &     operator    *=      (const Matrix<float, 4, Columns> &);
        inline constexpr float &            operator    []      (size_t position);
        inline constexpr float const &      operator    []      (size_t position) const;
        inline float                        dot                 (const Vector & v) const;
        inline constexpr float              dot_xyz             (const Vector & v) const;
        inline Vector                       cross               (const Vector & v) const;
        inline float                        length              () const;
        inline float                        length2             () const;
        inline Vector &                     normalize           ();
        inline Vector                       normalized          () const;
        inline std::string                  to_string           () const;
        inline constexpr const float *      c_array             () const;
        inline constexpr float *            c_array             ();
        inline constexpr float const &      x                   () const;
        inline constexpr float &            x                   ();
        inline constexpr float const &      y                   () const;
        inline constexpr float &            y                   ();
        inline constexpr float const &      z                   () const;
        inline constexpr float &            z                   ();
        inline constexpr float const &      w                   () const;
        inline constexpr float &            w                   ();
        inline Vector<float, 3>             xyz                 () const;
        inline Vector<float, 2>             xy                  () const;
        float                               components [4];
    };
}

ms::math::Vector<float, 4>::Vector(const Vector & v) {
    std::memcpy(components, v.components, 4 * sizeof(float));
}

ms::math::Vector<float, 4>::Vector (const Vector<float, 3> & v, float value) {
    std::memcpy(components, v.components, 3 * sizeof(float));
    components[3] = value;
}

ms::math::Vector<float, 4>::Vector(const float array [4]) {
    std::memcpy(components, array, 4 * sizeof(float));
}

ms::math::Vector<float, 4>::Vector (float x, float y, float z, float w) : components{x, y, z, w} { }

ms::math::Vector<float, 4> & ms::math::Vector<float, 4>::operator=(const Vector & v) {
    std::memcpy(components, v.components, 4 * sizeof(float));
    return *this;
}

ms::math::Vector<float, 4> :: Vector (const spco::RadiansSpherical <float> & sphericalCoordinates) {
    components[0] = sphericalCoordinates.radius * std::cos(sphericalCoordinates.azimuthAngle) * std::sin(sphericalCoordinates.inclination);
    components[1] = sphericalCoordinates.radius * std::sin(sphericalCoordinates.azimuthAngle) * std::sin(sphericalCoordinates.inclination);
    components[2] = sphericalCoordinates.radius * std::cos(sphericalCoordinates.inclination);
    components[3] = 1.0f;
}

bool ms::math::Vector<float, 4>::operator == (const Vector & v) const {
    return  v.components[0] == components[0] &&
            v.components[1] == components[1] &&
            v.components[2] == components[2] &&
            v.components[3] == components[3];
}


bool ms::math::Vector<float, 4>::operator != (const Vector & v) const {
    return  v.components[0] != components[0] ||
            v.components[1] != components[1] ||
            v.components[2] != components[2] ||
            v.components[3] != components[3];
}

float ms::math::Vector<float, 4>::dot(const Vector & v) const {
    return  components[0] * v.components[0] +
            components[1] * v.components[1] +
            components[2] * v.components[2] +
            components[3] * v.components[3];
}

constexpr float ms::math::Vector<float, 4>::dot_xyz(const Vector & v) const {
    return 	components[0] * v.components[0] +	components[1] * v.components[1] +	components[2] * v.components[2];
}

ms::math::Vector<float, 4> ms::math::Vector<float, 4>::cross (const Vector & v) const {
    return Vector(components[1] * v.components[2] - components[2] * v.components[1],
                  components[2] * v.components[0] - components[0] * v.components[2],
                  components[0] * v.components[1] - components[1] * v.components[0],
                  1.0f);
}

ms::math::Vector<float, 4> & ms::math::Vector<float, 4>::operator /= (float value) {
    components[0] /= value;
    components[1] /= value;
    components[2] /= value;
    components[3] /= value;
    return *this;
}


ms::math::Vector<float, 4> ms::math::Vector<float, 4>::operator / (float value) const {
    return Vector(components[0] / value, components[1] / value, components[2] / value, components[3] / value);
}

ms::math::Vector<float, 4> & ms::math::Vector<float, 4>::operator *= (float value) {
    components[0] *= value;
    components[1] *= value;
    components[2] *= value;
    components[3] *= value;
    return *this;
}


ms::math::Vector<float, 4> ms::math::Vector<float, 4>::operator * (float value) const {
    return Vector(components[0] * value, components[1] * value, components[2] * value, components[3] * value);
}

template <std::uint8_t Columns>
ms::math::Vector<float, Columns> ms::math::Vector<float, 4> :: operator * (const Matrix<float, 4, Columns> & m) const {
    Vector<float, Columns> result;
    for(std::uint8_t row = 0; row < 4; ++row) {
        result.components[row] = 0.0;
        for(std::uint8_t column = 0; column < Columns; ++column)
            result.components[row] += components[column] * m.components[4 * column + row];
    }
    return result;
}


template <std::uint8_t Columns>
ms::math::Vector<float, Columns> & ms::math::Vector<float, 4> :: operator *= (const Matrix<float, 4, Columns> & m) {
    Vector<float, Columns> result;
    result = (*this) * m;
    (*this) = result;
    return (*this);
}

constexpr float& ms::math::Vector<float, 4>::operator [] (size_t position) {
    return components[position];
}

constexpr const float& ms::math::Vector<float, 4>::operator [] (size_t position) const {
    return components[position];
}

ms::math::Vector<float, 4> ms::math::Vector<float, 4>::operator + (const Vector & v) const {
    return ms::math::Vector<float, 4>(v.components[0] + components[0],
                                      v.components[1] + components[1],
                                      v.components[2] + components[2],
                                      v.components[3] + components[3]);
}

ms::math::Vector<float, 4> ms::math::Vector<float, 4>::operator - (const Vector & v) const {
    return ms::math::Vector<float, 4>(components[0] - v.components[0],
                                      components[1] - v.components[1],
                                      components[2] - v.components[2],
                                      components[3] - v.components[3]);
}

ms::math::Vector<float, 4> & ms::math::Vector<float, 4>::operator += (const Vector & v) {
    components[0] += v.components[0];
    components[1] += v.components[1];
    components[2] += v.components[2];
    components[3] += v.components[3];
    return *this;
    
}

ms::math::Vector<float, 4> & ms::math::Vector<float, 4>::operator -= (const Vector & v) {
    components[0] -= v.components[0];
    components[1] -= v.components[1];
    components[2] -= v.components[2];
    components[3] -= v.components[3];
    return *this;
}

float ms::math::Vector<float, 4>::length() const {
    return std::sqrt(components[0] * components[0] + components[1] * components[1] + components[2] * components[2] + components[3] * components[3]);
}


float ms::math::Vector<float, 4>::length2() const {
    return components[0] * components[0] + components[1] * components[1] + components[2] * components[2] + components[3] * components[3];
}

ms::math::Vector<float, 4> ms::math::Vector<float, 4> :: operator - () const {
    return Vector(-components[0], -components[1], -components[2], -components[3]);
}

ms::math::Vector<float, 4> & ms::math::Vector<float, 4>::normalize() {
    float len = std::sqrt(components[0] * components[0] + components[1] * components[1] + components[2] * components[2] + components[3] * components[3]);
    components[0] /= len;
    components[1] /= len;
    components[2] /= len;
    components[3] /= len;
    return *this;
}

ms::math::Vector<float, 4> ms::math::Vector<float, 4> :: normalized() const {
    float len = std::sqrt(components[0] * components[0] + components[1] * components[1] + components[2] * components[2] + components[3] * components[3]);
    return Vector(components[0]/len, components[1]/len, components[2]/len, components[3]/len);
}

std::string ms::math::Vector<float, 4>::to_string() const {
    std::ostringstream output;
    output << components[0] << " ";
    output << components[1] << " ";
    output << components[2] << " ";
    output << components[3] << " ";
    return output.str();
}

constexpr const float * ms::math::Vector<float, 4>::c_array() const {
    return components;
}

constexpr float * ms::math::Vector<float, 4>::c_array() {
    return components;
}

constexpr float const & ms::math::Vector <float, 4>::x () const {
    return *components;
}

constexpr float & ms::math::Vector <float, 4>::x () {
    return *components;
}

constexpr float const & ms::math::Vector <float, 4>::y () const {
    return *(components + 1);
}

constexpr float & ms::math::Vector <float, 4>::y () {
    return *(components + 1);
}

constexpr float const & ms::math::Vector <float, 4>::z () const  {
    return *(components + 2);
}

constexpr float & ms::math::Vector <float, 4>::z ()  {
    return *(components + 2);
}

constexpr float const & ms::math::Vector <float, 4>::w () const  {
    return *(components + 3);
}


constexpr float & ms::math::Vector <float, 4>::w () {
    return *(components + 3);
}

ms::math::Vector <float, 3> ms::math::Vector <float, 4>::xyz () const {
    return Vector <float, 3>{x(), y(), z()};
}

ms::math::Vector <float, 2> ms::math::Vector <float, 4>::xy () const {
    return Vector <float, 2>{x(), y()};
}

ms::math::Vector<float, 5> ms::math::Vector<float, 4>::expanded (float value) const {
    return Vector<float, 5>(components[0], components[1], components[2], components[3], value);
}
