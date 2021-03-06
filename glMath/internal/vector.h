//
//  vector.h
//  glMath
//
//  Created by Mateusz Stompór on 22/02/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#pragma once

#include <string>
#include <sstream>
#include <cstring>

#include "common.h"
#include "matrix.h"

namespace ms::math {
    namespace spco {
        template <typename Type>
        struct RadiansSpherical;
    }
    template <typename Type, std::uint8_t Dimension>
    class Vector {
        template <typename T, std::uint8_t Rows, std::uint8_t Columns>
        friend class Matrix;
    public:
                                    Vector              ();
                                    Vector              (Type value);
                                    Vector              (const Vector & v);
                                    Vector              (const Vector<Type, Dimension - 1> & v, Type value);
                                    Vector              (const Type array [Dimension]);
                                    Vector              (Type x, Type y);
                                    Vector              (Type x, Type y, Type z);
                                    Vector              (Type x, Type y, Type z, Type w);
                                    Vector              (Type x, Type y, Type z, Type w, Type p);
                                    Vector              (const spco::RadiansSpherical<Type> & sphericalCoordinates);
        Vector &                    operator    =       (const Vector & v);
        bool                        operator    ==      (const Vector & v) const;
        bool                        operator    !=      (const Vector & v) const;
        Vector                      operator    +       (const Vector & v) const;
        Vector &                    operator    +=      (const Vector & v);
        Vector                      operator    -       (const Vector & v) const;
        Vector &                    operator    -=      (const Vector & v);
        Vector                      operator    -       () const;
        Vector                      operator    /       (Type value) const;
        Vector &                    operator    /=      (Type value);
        Vector                      operator    *       (Type value) const;
        Vector &                    operator    *=      (Type value);
        template <std::uint8_t Columns>
        Vector<Type, Columns>       operator    *       (const Matrix<Type, Dimension, Columns> &) const;
        template <std::uint8_t Columns>
        Vector<Type, Columns> &     operator    *=      (const Matrix<Type, Dimension, Columns> &);
        constexpr Type &            operator    []      (size_t position);
        constexpr Type const &      operator    []      (size_t position) const;
        Type                        dot                 (const Vector & v) const;
        constexpr Type              dot_xyz             (const Vector & v) const;
        Vector                      cross               (const Vector & v) const;
        Type                        length              () const;
        Type                        length2             () const;
        Vector &                    normalize           ();
        Vector                      normalized          () const;
        std::string                 to_string           () const;
        constexpr Type *            c_array             ();
        constexpr const Type *      c_array             () const;
        constexpr Type const &      x                   () const;
        constexpr Type &            x                   ();
        constexpr Type const &      y                   () const;
        constexpr Type &            y                   ();
        constexpr Type const &      z                   () const;
        constexpr Type &            z                   ();
        constexpr Type const &      w                   () const;
        constexpr Type &            w                   ();
        Vector<Type, 3>             xyz                 () const;
        Vector<Type, 2>             xy                  ()const;
        Type                        components [Dimension];
    };
}

template <typename Type, std::uint8_t Dimension>
ms::math::Vector<Type, Dimension>::Vector() { }

template <typename Type, std::uint8_t Dimension>
ms::math::Vector<Type, Dimension>::Vector(Type value) : Vector() {
    static_assert(Dimension == 1, "Dimension must equal 1");
    *(components) = value;
}

template <typename Type, std::uint8_t Dimension>
ms::math::Vector<Type, Dimension>::Vector(const Vector & v) : Vector() {
    std::memcpy(components, v.components, Dimension * sizeof(Type));
}

template <typename Type, std::uint8_t Dimension>
ms::math::Vector<Type, Dimension>::Vector (const Vector<Type, Dimension - 1> & v, Type value) : Vector() {
    std::memcpy(components, v.components, (Dimension - 1) * sizeof(Type));
    components[Dimension - 1] = value;
}

template <typename Type, std::uint8_t Dimension>
ms::math::Vector<Type, Dimension>::Vector(const Type array [Dimension]) : Vector() {
    std::memcpy(components, array, Dimension * sizeof(Type));
}


template <typename Type, std::uint8_t Dimension>
ms::math::Vector<Type, Dimension>::Vector (Type x, Type y) : Vector() {
    static_assert(Dimension == 2, "Dimension must equal 2");
    *(components) = x;
    *(components + 1) = y;
}

template <typename Type, std::uint8_t Dimension>
ms::math::Vector<Type, Dimension>::Vector (Type x, Type y, Type z) : Vector() {
    static_assert(Dimension == 3, "Dimension must equal 3");
    *(components) = x;
    *(components + 1) = y;
    *(components + 2) = z;
}

template <typename Type, std::uint8_t Dimension>
ms::math::Vector<Type, Dimension>::Vector (Type x, Type y, Type z, Type w) : Vector() {
    static_assert(Dimension == 4, "Dimension must equal 4");
    *(components) = x;
    *(components + 1) = y;
    *(components + 2) = z;
    *(components + 3) = w;
}

template <typename Type, std::uint8_t Dimension>
ms::math::Vector<Type, Dimension>::Vector (Type x, Type y, Type z, Type w, Type p) : Vector() {
    static_assert(Dimension == 5, "Dimension must equal 5");
    *(components) = x;
    *(components + 1) = y;
    *(components + 2) = z;
    *(components + 3) = w;
    *(components + 4) = p;
}

template <typename Type, std::uint8_t Dimension>
ms::math::Vector<Type, Dimension>& ms::math::Vector<Type, Dimension>::operator=(const Vector & v) {
    std::memcpy(components, v.components, Dimension * sizeof(Type));
    return *this;
}

template <typename Type, std::uint8_t Dimension>
ms::math::Vector<Type, Dimension> :: Vector (const spco::RadiansSpherical <Type> & sphericalCoordinates) : Vector() {
    static_assert(Dimension == 3, "Spherical system requires dimension of three");
    components[0] = sphericalCoordinates.radius * cos(sphericalCoordinates.azimuthAngle) * sin(sphericalCoordinates.inclination);
    components[1] = sphericalCoordinates.radius * sin(sphericalCoordinates.azimuthAngle) * sin(sphericalCoordinates.inclination);
    components[2] = sphericalCoordinates.radius * cos(sphericalCoordinates.inclination);
}

template <typename Type, std::uint8_t Dimension>
bool ms::math::Vector<Type, Dimension>::operator == (const Vector & v) const {
    return std::equal(std::begin(components), std::end(components), std::begin(v.components));
}

template <typename Type, std::uint8_t Dimension>
bool ms::math::Vector<Type, Dimension>::operator != (const Vector & v) const {
    return !(*this == v);
}

template <typename Type, std::uint8_t Dimension>
Type ms::math::Vector<Type, Dimension>::dot(const Vector & v) const {
    Type dot = Type{0.0};
    for(std::uint8_t i = 0; i < Dimension; ++i)
        dot += components[i] * v.components[i];
    return dot;
}

template <typename Type, std::uint8_t Dimension>
constexpr Type ms::math::Vector<Type, Dimension>::dot_xyz (const Vector & v) const {
    static_assert(Dimension >= 3, "dot_xyz requires vector of dimension at least 3");
    return components[0] * v.components[0] + components[1] * v.components[1] + components[2] * v.components[2];
}

template <typename Type, std::uint8_t Dimension>
ms::math::Vector<Type, Dimension> ms::math::Vector<Type, Dimension>::cross(const Vector & v) const {
    static_assert(Dimension == 3, "Cross product exists only for dimension of three");
    Vector vec;
    vec[0] = components[1] * v.components[2] - components[2] * v.components[1];
    vec[1] = components[2] * v.components[0] - components[0] * v.components[2];
    vec[2] = components[0] * v.components[1] - components[1] * v.components[0];
    return vec;
}

template <typename Type, std::uint8_t Dimension>
ms::math::Vector<Type, Dimension> & ms::math::Vector<Type, Dimension>::operator /= (Type value) {
    for(std::uint8_t i = 0; i < Dimension; ++i)
        components[i] /= value;
    return *this;
}

template <typename Type, std::uint8_t Dimension>
ms::math::Vector<Type, Dimension> ms::math::Vector<Type, Dimension>::operator / (Type value) const {
    Vector vec;
    for(std::uint8_t i{0}; i < Dimension; ++i)
        vec.components[i] = components[i] / value;
    return vec;
}

template <typename Type, std::uint8_t Dimension>
ms::math::Vector<Type, Dimension> & ms::math::Vector<Type, Dimension>::operator *= (Type value) {
    for(std::uint8_t i = 0; i < Dimension; ++i)
        components[i] *= value;
    return *this;
}

template <typename Type, std::uint8_t Dimension>
ms::math::Vector<Type, Dimension> ms::math::Vector<Type, Dimension>::operator * (Type value) const {
    Vector vec;
    for(std::uint8_t i = 0; i < Dimension; ++i)
        vec.components[i] = components[i] * value;
    return vec;
}

template <typename Type, std::uint8_t Dimension>
template <std::uint8_t Columns>
ms::math::Vector<Type, Columns> ms::math::Vector<Type, Dimension> :: operator * (const Matrix<Type, Dimension, Columns> & m) const {
    Vector<Type, Columns> result;
    for(std::uint8_t row = 0; row < Dimension; ++row) {
        result.components[row] = 0.0;
        for(std::uint8_t column = 0; column < Columns; ++column)
            result.components[row] += components[column] * m.components[Dimension * column + row];
    }
    return result;
}

template <typename Type, std::uint8_t Dimension>
template <std::uint8_t Columns>
ms::math::Vector<Type, Columns> & ms::math::Vector<Type, Dimension> :: operator *= (const Matrix<Type, Dimension, Columns> & m) {
    auto result = *this * m;
    *this = result;
    return *this;
}

template <typename Type, std::uint8_t Dimension>
constexpr Type& ms::math::Vector<Type, Dimension>::operator [] (size_t position) {
    return components[position];
}

template <typename Type, std::uint8_t Dimension>
constexpr const Type& ms::math::Vector<Type, Dimension>::operator [] (size_t position) const {
    return components[position];
}

template <typename Type, std::uint8_t Dimension>
ms::math::Vector<Type, Dimension> operator * (Type value, const ms::math::Vector<Type, Dimension> & v) {
    ms::math::Vector<Type, Dimension> vec(v);
    return vec * value;
}

template <typename Type, std::uint8_t Dimension>
ms::math::Vector<Type, Dimension> ms::math::Vector<Type, Dimension>::operator + (const Vector & v) const {
    Vector vec{};
    for(std::uint8_t i = 0; i < Dimension; ++i)
        vec.components[i] = components[i] + v.components[i];
    return vec;
}

template <typename Type, std::uint8_t Dimension>
ms::math::Vector<Type, Dimension> ms::math::Vector<Type, Dimension>::operator - (const Vector & v) const {
    Vector vec;
    for(std::uint8_t i = 0; i < Dimension; ++i)
        vec.components[i] = components[i] - v.components[i];
    return vec;
}

template <typename Type, std::uint8_t Dimension>
ms::math::Vector<Type, Dimension> & ms::math::Vector<Type, Dimension>::operator += (const Vector & v) {
    for(std::uint8_t i = 0; i < Dimension; ++i)
        components[i] += v.components[i];
    return *this;
}

template <typename Type, std::uint8_t Dimension>
ms::math::Vector<Type, Dimension> & ms::math::Vector<Type, Dimension>::operator -= (const Vector & v) {
    for(std::uint8_t i = 0; i < Dimension; ++i)
        components[i] -= v.components[i];
    return *this;
}

template <typename Type, std::uint8_t Dimension>
Type ms::math::Vector<Type, Dimension>::length() const {
    Type length {0.0};
    for(std::uint8_t i = 0; i < Dimension; ++i) {
        length += components[i] * components[i];
    }
    return sqrt(length);
}

template <typename Type, std::uint8_t Dimension>
Type ms::math::Vector<Type, Dimension>::length2() const {
    return dot(*this);
}

template <typename Type, std::uint8_t Dimension>
ms::math::Vector<Type, Dimension> & ms::math::Vector<Type, Dimension>::normalize() {
    Type len = length();
    for(std::uint8_t i = 0; i < Dimension; ++i)
        components[i] /= len;
    return *this;
}

template <typename Type, std::uint8_t Dimension>
ms::math::Vector<Type, Dimension> ms::math::Vector<Type, Dimension> :: normalized() const {
    Vector vec{*this};
    vec.normalize();
    return vec;
}

template <typename Type, std::uint8_t Dimension>
std::string ms::math::Vector<Type, Dimension>::to_string() const {
    std::ostringstream output;
    for (std::uint8_t i = 0; i < Dimension; ++i)
        output << components[i] << " ";
    return output.str();
}

template <typename Type, std::uint8_t Dimension>
constexpr const Type * ms::math::Vector<Type, Dimension>::c_array() const {
    return components;
}

template <typename Type, std::uint8_t Dimension>
constexpr Type * ms::math::Vector<Type, Dimension>::c_array() {
    return components;
}

template <typename Type, std::uint8_t Dimension>
constexpr Type const & ms::math::Vector<Type, Dimension>::x () const {
    static_assert(Dimension > 0, "Dimension needs to be greater than zero");
    return *components;
}

template <typename Type, std::uint8_t Dimension>
constexpr Type & ms::math::Vector<Type, Dimension>::x () {
    static_assert(Dimension > 0, "Dimension needs to be greater than zero");
    return *components;
}

template <typename Type, std::uint8_t Dimension>
constexpr Type const & ms::math::Vector<Type, Dimension>::y () const {
    static_assert(Dimension > 1, "Dimension needs to be greater than one");
    return *(components + 1);
}

template <typename Type, std::uint8_t Dimension>
constexpr Type & ms::math::Vector<Type, Dimension>::y () {
    static_assert(Dimension > 1, "Dimension needs to be greater than one");
    return *(components + 1);
}

template <typename Type, std::uint8_t Dimension>
constexpr Type const & ms::math::Vector<Type, Dimension>::z () const  {
    static_assert(Dimension > 2, "Dimension needs to be greater than two");
    return *(components + 2);
}

template <typename Type, std::uint8_t Dimension>
constexpr Type & ms::math::Vector<Type, Dimension>::z ()  {
    static_assert(Dimension > 2, "Dimension needs to be greater than two");
    return *(components + 2);
}

template <typename Type, std::uint8_t Dimension>
constexpr Type const & ms::math::Vector<Type, Dimension>::w () const  {
    static_assert(Dimension > 3, "Dimension needs to be greater than three");
    return *(components + 3);
}

template <typename Type, std::uint8_t Dimension>
constexpr Type & ms::math::Vector<Type, Dimension>::w () {
    static_assert(Dimension > 3, "Dimension needs to be greater than three");
    return *(components + 3);
}

template <typename Type, std::uint8_t Dimension>
ms::math::Vector<Type, 3> ms::math::Vector<Type, Dimension>::xyz () const {
    return Vector<Type, 3>{x(), y(), z()};
}

template <typename Type, std::uint8_t Dimension>
ms::math::Vector<Type, Dimension> ms::math::Vector<Type, Dimension> :: operator - () const {
    Vector v;
    for (size_t i = 0; i < Dimension; ++i)
        v.components[i] = -components[i];
    return v;
}

template <typename Type, std::uint8_t Dimension>
ms::math::Vector<Type, 2> ms::math::Vector<Type, Dimension>::xy () const {
    return Vector<Type, 2>{x(), y()};
}
