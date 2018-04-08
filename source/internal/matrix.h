//
//  matrix.h
//  glMath
//
//  Created by Mateusz Stompór on 22/02/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#ifndef matrix_h
#define matrix_h

#include <string>
#include <cstring>
#include <sstream>
#include <iomanip>

#include "common.h"

namespace ms {
	
	namespace math {
	
		template <typename T, UNSIGNED_TYPE Dimension>
		class Vector;
		
//		template <>
//		class Vector<float, 4>;
		
		template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
		class Matrix {
			
		template <typename T, UNSIGNED_TYPE Dimension>
		friend class Vector;
			
		public:
			
			//static functions
			
			static Matrix 				identity			();
			static Matrix 				diagonal			(Type value);
			
			
		public:
			
										Matrix				();
										Matrix				(Type value);
										Matrix				(const Matrix & m);
										Matrix				(Matrix && m) noexcept;
										Matrix				(const Type array [Rows * Columns]);
			
										~Matrix				();
			
			Matrix &					operator =			(const Matrix & m);
			Matrix &					operator =			(Matrix && m) noexcept;
			
			Matrix 						operator - 			(const Matrix & m) const;
			Matrix & 					operator -= 		(const Matrix & m);
			
			Matrix 						operator + 			(const Matrix & m) const;
			Matrix & 					operator += 		(const Matrix & m);
			
			Matrix & 					operator *= 		(const Matrix & m);
			
			template <UNSIGNED_TYPE C>
			Matrix<Type, Rows, C> 		operator * 			(const Matrix<Type, Columns, C> & m) const;
			
			Vector<Type, Rows>			operator *			(const Vector<Type, Columns> &) const;
			
			Matrix & 					operator *= 		(Type value);
			Matrix	 					operator *	 		(Type value) const;
			
			bool	 					operator ==	 		(const Matrix & m);
			bool	 					operator !=	 		(const Matrix & m);
			
			Matrix<Type, Columns, Rows> transposition 		() const;
			
			Type & 						operator []			(UNSIGNED_TYPE index);
			const Type & 				operator []			(UNSIGNED_TYPE index) const;
			
			std::string 				to_string			() const;
			
			Type *		 				c_array				();
			const Type * 				c_array				() const;
			
//		private:
			
			Type * 						components;
			
		};
		
	}
	
}

template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
ms::math::Matrix<Type, Rows, Columns> ms::math::Matrix<Type, Rows, Columns> :: identity () {
	return diagonal(Type(1.0));
}

template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
ms::math::Matrix<Type, Rows, Columns> ms::math::Matrix<Type, Rows, Columns> :: diagonal (Type value) {
	static_assert(Rows == Columns, "Diagonal matrix needs to be square");
	Matrix m;
	for(UNSIGNED_TYPE row = 0; row < Rows; ++row)
		for(UNSIGNED_TYPE column = 0; column < Columns; ++column)
			m.components[column * Rows + row] = row == column ? value : 0;
	return m;
}

template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
ms::math::Matrix<Type, Rows, Columns> :: Matrix() : components(new Type[ Columns * Rows ]) { }

template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
ms::math::Matrix<Type, Rows, Columns> :: Matrix(Type value) : Matrix() {
	for(UNSIGNED_TYPE i = 0; i < Rows * Columns; ++i)
		(*this).components[i] = value;
}

template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
ms::math::Matrix<Type, Rows, Columns> :: Matrix(const Matrix & m) : Matrix() {
	std::memcpy((*this).components, m.components, sizeof(Type) * Rows * Columns);
}

template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
ms::math::Matrix<Type, Rows, Columns> :: Matrix(Matrix && m) noexcept {
	(*this).components = m.components;
	m.components = nullptr;
}

template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
ms::math::Matrix<Type, Rows, Columns> :: Matrix(const Type array [Rows * Columns]) : Matrix() {
	std::memcpy((*this).components, array, sizeof(Type) * Rows * Columns);
}

template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
ms::math::Matrix<Type, Rows, Columns> :: ~Matrix() {
	delete [] (*this).components;
}

template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
ms::math::Matrix<Type, Rows, Columns> & ms::math::Matrix<Type, Rows, Columns> :: operator = (const Matrix & m) {
	std::memcpy((*this).components, m.components, sizeof(Type) * Rows * Columns);
	return (*this);
}

template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
ms::math::Matrix<Type, Rows, Columns> & ms::math::Matrix<Type, Rows, Columns> :: operator = (Matrix && m) noexcept {
	delete [] (*this).components;
	(*this).components = m.components;
	m.components = nullptr;
	return (*this);
}

template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
ms::math::Matrix<Type, Rows, Columns> ms::math::Matrix<Type, Rows, Columns> :: operator - (const Matrix & m) const {
	Matrix result;
	for(UNSIGNED_TYPE i = 0; i < Rows * Columns; ++i)
		result[i] = this->components[i] - m.components[i];
	return result;
}

template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
ms::math::Matrix<Type, Rows, Columns> & ms::math::Matrix<Type, Rows, Columns> :: operator -= (const Matrix & m) {
	for(UNSIGNED_TYPE i = 0; i < Rows * Columns; ++i)
		this->components -= m.components[i];
	return *this;
}

template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
ms::math::Matrix<Type, Rows, Columns> ms::math::Matrix<Type, Rows, Columns> :: operator + (const Matrix & m) const {
	Matrix result;
	for(UNSIGNED_TYPE i = 0; i < Rows * Columns; ++i)
		result[i] = this->components[i] + m.components[i];
	return result;
}

template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
ms::math::Matrix<Type, Rows, Columns> & ms::math::Matrix<Type, Rows, Columns> :: operator += (const Matrix & m) {
	for(UNSIGNED_TYPE i = 0; i < Rows * Columns; ++i)
		this->components += m.components[i];
	return *this;
}

template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
ms::math::Matrix<Type, Rows, Columns> & ms::math::Matrix<Type, Rows, Columns> :: operator *= (const Matrix & m) {
	(*this) = (*this) * m;
	return (*this);
}

template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
template <UNSIGNED_TYPE C>
ms::math::Matrix<Type, Rows, C> ms::math::Matrix<Type, Rows, Columns> :: operator * (const Matrix<Type, Columns, C> & m) const {
	Matrix <Type, Rows, C> result;

	for(UNSIGNED_TYPE outerIterator = 0; outerIterator < Rows; ++outerIterator)
		for (UNSIGNED_TYPE innerIterator = 0; innerIterator < C; ++innerIterator) {
			result.components[Rows * innerIterator + outerIterator] = 0;
			for (UNSIGNED_TYPE i = 0; i < Columns; ++i)
				result.components[Rows * innerIterator + outerIterator] += this->components[Rows*i + outerIterator ] * m.components[Rows*innerIterator + i];
		}
	
	return result;
}

template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
ms::math::Vector<Type, Rows> ms::math::Matrix<Type, Rows, Columns> :: operator * (const Vector<Type, Columns> & v) const {
	Vector<Type, Rows> result;
	for(UNSIGNED_TYPE row = 0; row < Rows; ++row) {
		result.components[row] = 0.0;
		for(UNSIGNED_TYPE column = 0; column < Columns; ++column)
			result.components[row] += v.components[column] * this->components[Rows * column + row];
	}
	return result;
}

template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
ms::math::Matrix<Type, Rows, Columns> & ms::math::Matrix<Type, Rows, Columns> :: operator *= (Type value) {
	for(UNSIGNED_TYPE i = 0; i < Rows * Columns; ++i)
		(*this).components *= value;
	return (*this);
}

template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
ms::math::Matrix<Type, Rows, Columns> ms::math::Matrix<Type, Rows, Columns> :: operator * (Type value) const {
	Matrix result;
	for(UNSIGNED_TYPE i = 0; i < Rows * Columns; ++i)
		result[i] = (*this).components[i] * value;
	return result;
}

template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
bool ms::math::Matrix<Type, Rows, Columns> :: operator == (const Matrix & m) {
	return !((*this) != m);
}

template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
bool ms::math::Matrix<Type, Rows, Columns> :: operator != (const Matrix & m) {
	for(UNSIGNED_TYPE i = 0; i < Rows * Columns; ++i) {
		if (m.components[i] != (*this).components[i])
			return true;
	}
	return false;
}

template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
ms::math::Matrix<Type, Columns, Rows> ms::math::Matrix<Type, Rows, Columns> :: transposition () const {
	Matrix<Type, Columns, Rows> mat;
	for (UNSIGNED_TYPE row = 0; row < Rows; ++row)
		for (UNSIGNED_TYPE column = 0; column < Columns; ++column)
			mat.components[row * Columns + column] = this->components[row + column * Rows];
	return mat;
}

template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
Type & ms::math::Matrix<Type, Rows, Columns> :: operator [] (UNSIGNED_TYPE index) {
	return this->components[index];
}

template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
const Type & ms::math::Matrix<Type, Rows, Columns> :: operator [] (UNSIGNED_TYPE index) const {
	return this->components[index];
}

template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
std::string ms::math::Matrix<Type, Rows, Columns> :: to_string() const {
	std::ostringstream output;
	for (UNSIGNED_TYPE row = 0; row < Rows; ++row) {
		for (UNSIGNED_TYPE column = 0; column < Columns; ++column) {
			output << std::setprecision(2) << components[column * Rows + row] << " ";
		}
		output << std::endl;
	}
	return output.str();
}

template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
const Type * ms::math::Matrix<Type, Rows, Columns> :: c_array() const {
	return this->components;
}

template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
Type * ms::math::Matrix<Type, Rows, Columns> :: c_array() {
	return this->components;
}

#endif
