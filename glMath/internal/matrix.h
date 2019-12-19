//
//  matrix.h
//  glMath
//
//  Created by Mateusz Stompór on 22/02/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#pragma once

#include <string>
#include <cstring>
#include <sstream>
#include <iomanip>

#include "common.h"

namespace ms::math {
    template <typename T, std::uint8_t Dimension>
    class Vector;
    template <typename Type, std::uint8_t Rows, std::uint8_t Columns>
    class Matrix {
        template <typename T, std::uint8_t Dimension>
        friend class Vector;
    public:
        //static functions
        static Matrix               identity            ();
        static Matrix               diagonal            (Type value);
    public:
                                    Matrix              () = default;
                                    Matrix              (Type value);
                                    Matrix              (const Matrix & m);
                                    Matrix              (const Type array [Rows * Columns]);
        Matrix &                    operator =          (const Matrix & m);
        Matrix                      operator -          (const Matrix & m) const;
        Matrix &                    operator -=         (const Matrix & m);
        Matrix                      operator +          (const Matrix & m) const;
        Matrix &                    operator +=         (const Matrix & m);
        Matrix &                    operator *=         (const Matrix & m);
        template <std::uint8_t C>
        Matrix<Type, Rows, C>       operator *          (const Matrix<Type, Columns, C> & m) const;
        Vector<Type, Rows>          operator *          (const Vector<Type, Columns> &) const;
        Matrix &                    operator *=         (Type value);
        Matrix                      operator *          (Type value) const;
        bool                        operator ==         (const Matrix & m) const;
        bool                        operator !=         (const Matrix & m) const;
        Matrix<Type, Columns, Rows> transposition       () const;
        constexpr Type &            operator []         (std::uint8_t index);
        constexpr const Type &      operator []         (std::uint8_t index) const;
        std::string                 to_string           () const;
        constexpr Type *            c_array             ();
        constexpr const Type *      c_array             () const;
        Type                        components [Rows * Columns];
    };
}

template <typename Type, std::uint8_t Rows, std::uint8_t Columns>
ms::math::Matrix<Type, Rows, Columns> ms::math::Matrix<Type, Rows, Columns> :: identity () {
    return diagonal(Type(1.0));
}

template <typename Type, std::uint8_t Rows, std::uint8_t Columns>
ms::math::Matrix<Type, Rows, Columns> ms::math::Matrix<Type, Rows, Columns> :: diagonal (Type value) {
    static_assert(Rows == Columns, "Diagonal matrix needs to be square");
    Matrix m;
    for(std::uint8_t row = 0; row < Rows; ++row)
        for(std::uint8_t column = 0; column < Columns; ++column)
            m.components[column * Rows + row] = row == column ? value : 0;
    return m;
}

template <typename Type, std::uint8_t Rows, std::uint8_t Columns>
ms::math::Matrix<Type, Rows, Columns> :: Matrix(Type value) : Matrix() {
    for(std::uint8_t i = 0; i < Rows * Columns; ++i)
        components[i] = value;
}

template <typename Type, std::uint8_t Rows, std::uint8_t Columns>
ms::math::Matrix<Type, Rows, Columns> :: Matrix(const Matrix & m) : Matrix() {
    std::memcpy(components, m.components, sizeof(Type) * Rows * Columns);
}

template <typename Type, std::uint8_t Rows, std::uint8_t Columns>
ms::math::Matrix<Type, Rows, Columns> :: Matrix(const Type array [Rows * Columns]) : Matrix() {
    std::memcpy(components, array, sizeof(Type) * Rows * Columns);
}

template <typename Type, std::uint8_t Rows, std::uint8_t Columns>
ms::math::Matrix<Type, Rows, Columns> & ms::math::Matrix<Type, Rows, Columns> :: operator = (const Matrix & m) {
    std::memcpy(components, m.components, sizeof(Type) * Rows * Columns);
    return (*this);
}

template <typename Type, std::uint8_t Rows, std::uint8_t Columns>
ms::math::Matrix<Type, Rows, Columns> ms::math::Matrix<Type, Rows, Columns> :: operator - (const Matrix & m) const {
    Matrix result;
    for(std::uint8_t i = 0; i < Rows * Columns; ++i)
        result[i] = components[i] - m.components[i];
    return result;
}

template <typename Type, std::uint8_t Rows, std::uint8_t Columns>
ms::math::Matrix<Type, Rows, Columns> & ms::math::Matrix<Type, Rows, Columns> :: operator -= (const Matrix & m) {
    for(std::uint8_t i = 0; i < Rows * Columns; ++i)
        components -= m.components[i];
    return *this;
}

template <typename Type, std::uint8_t Rows, std::uint8_t Columns>
ms::math::Matrix<Type, Rows, Columns> ms::math::Matrix<Type, Rows, Columns> :: operator + (const Matrix & m) const {
    Matrix result;
    for(std::uint8_t i = 0; i < Rows * Columns; ++i)
        result[i] = components[i] + m.components[i];
    return result;
}

template <typename Type, std::uint8_t Rows, std::uint8_t Columns>
ms::math::Matrix<Type, Rows, Columns> & ms::math::Matrix<Type, Rows, Columns> :: operator += (const Matrix & m) {
    for(std::uint8_t i = 0; i < Rows * Columns; ++i)
        components += m.components[i];
    return *this;
}

template <typename Type, std::uint8_t Rows, std::uint8_t Columns>
ms::math::Matrix<Type, Rows, Columns> & ms::math::Matrix<Type, Rows, Columns> :: operator *= (const Matrix & m) {
    (*this) = (*this) * m;
    return (*this);
}

template <typename Type, std::uint8_t Rows, std::uint8_t Columns>
template <std::uint8_t C>
ms::math::Matrix<Type, Rows, C> ms::math::Matrix<Type, Rows, Columns> :: operator * (const Matrix<Type, Columns, C> & m) const {
    Matrix <Type, Rows, C> result;
    
    for(std::uint8_t outerIterator = 0; outerIterator < Rows; ++outerIterator)
        for (std::uint8_t innerIterator = 0; innerIterator < C; ++innerIterator) {
            result.components[Rows * innerIterator + outerIterator] = 0;
            for (std::uint8_t i = 0; i < Columns; ++i)
                result.components[Rows * innerIterator + outerIterator] += this->components[Rows*i + outerIterator ] * m.components[Rows*innerIterator + i];
        }
    return result;
}

template <typename Type, std::uint8_t Rows, std::uint8_t Columns>
ms::math::Vector<Type, Rows> ms::math::Matrix<Type, Rows, Columns> :: operator * (const Vector<Type, Columns> & v) const {
    Vector<Type, Rows> result;
    for(std::uint8_t row = 0; row < Rows; ++row) {
        result.components[row] = 0.0;
        for(std::uint8_t column = 0; column < Columns; ++column)
            result.components[row] += v.components[column] * this->components[Rows * column + row];
    }
    return result;
}

template <typename Type, std::uint8_t Rows, std::uint8_t Columns>
ms::math::Matrix<Type, Rows, Columns> & ms::math::Matrix<Type, Rows, Columns> :: operator *= (Type value) {
    for(std::uint8_t i = 0; i < Rows * Columns; ++i)
        (*this).components *= value;
    return (*this);
}

template <typename Type, std::uint8_t Rows, std::uint8_t Columns>
ms::math::Matrix<Type, Rows, Columns> ms::math::Matrix<Type, Rows, Columns> :: operator * (Type value) const {
    Matrix result;
    for(std::uint8_t i = 0; i < Rows * Columns; ++i)
        result[i] = (*this).components[i] * value;
    return result;
}

template <typename Type, std::uint8_t Rows, std::uint8_t Columns>
bool ms::math::Matrix<Type, Rows, Columns> :: operator == (const Matrix & m) const {
    return std::equal(std::begin(components), std::end(components), std::begin(m.components));
}

template <typename Type, std::uint8_t Rows, std::uint8_t Columns>
bool ms::math::Matrix<Type, Rows, Columns> :: operator != (const Matrix & m) const {
    return !(*this == m);
}

template <typename Type, std::uint8_t Rows, std::uint8_t Columns>
ms::math::Matrix<Type, Columns, Rows> ms::math::Matrix<Type, Rows, Columns> :: transposition () const {
    Matrix<Type, Columns, Rows> mat;
    for (std::uint8_t row = 0; row < Rows; ++row)
        for (std::uint8_t column = 0; column < Columns; ++column)
            mat.components[row * Columns + column] = this->components[row + column * Rows];
    return mat;
}

template <typename Type, std::uint8_t Rows, std::uint8_t Columns>
constexpr Type & ms::math::Matrix<Type, Rows, Columns> :: operator [] (std::uint8_t index) {
    return components[index];
}

template <typename Type, std::uint8_t Rows, std::uint8_t Columns>
constexpr const Type & ms::math::Matrix<Type, Rows, Columns> :: operator [] (std::uint8_t index) const {
    return components[index];
}

template <typename Type, std::uint8_t Rows, std::uint8_t Columns>
std::string ms::math::Matrix<Type, Rows, Columns> :: to_string() const {
    std::ostringstream output;
    for (std::uint8_t row = 0; row < Rows; ++row) {
        for (std::uint8_t column = 0; column < Columns; ++column)
            output << std::setprecision(2) << components[column * Rows + row] << " ";
        output << '\n';
    }
    return output.str();
}

template <typename Type, std::uint8_t Rows, std::uint8_t Columns>
constexpr const Type * ms::math::Matrix<Type, Rows, Columns> :: c_array() const {
    return components;
}

template <typename Type, std::uint8_t Rows, std::uint8_t Columns>
constexpr Type * ms::math::Matrix<Type, Rows, Columns> :: c_array() {
    return components;
}
