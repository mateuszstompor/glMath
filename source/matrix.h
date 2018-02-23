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

#include "common.h"

namespace ms {
	
	namespace math {
	
		template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
		class Matrix {
			
		public:
			
							Matrix				();
							Matrix				(Type value);
							Matrix				(const Matrix & m);
							Matrix				(Matrix && m);
							Matrix				(const Type array [Rows * Columns]);
			
							~Matrix				();
			
			Matrix &		operator =			(const Matrix & m);
			Matrix &		operator =			(Matrix && m);
			
			Matrix 			operator - 			(const Matrix & m) const;
			Matrix & 		operator -= 		(const Matrix & m);
			
			Matrix 			operator + 			(const Matrix & m) const;
			Matrix & 		operator += 		(const Matrix & m);
			
			Matrix & 		operator *= 		(const Matrix & m);
			Matrix	 		operator *	 		(const Matrix & m) const;
			Matrix & 		operator *= 		(Type value);
			Matrix	 		operator *	 		(Type value) const;
			
			bool	 		operator ==	 		(const Matrix & m);
			bool	 		operator !=	 		(const Matrix & m);
			
			Type & 			operator []			(UNSIGNED_TYPE index);
			
			std::string 	to_string			() const;
			
			const Type * 	c_array				() const;
			
		private:
			
			Type * 			components;
			
		};
		
	}
	
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
ms::math::Matrix<Type, Rows, Columns> :: Matrix(Matrix && m) : components(m.components) {
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
ms::math::Matrix<Type, Rows, Columns> & ms::math::Matrix<Type, Rows, Columns> :: operator = (Matrix && m) {
	(*this).components = m.components;
	m.components = nullptr;
	return (*this);
}

template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
ms::math::Matrix<Type, Rows, Columns> ms::math::Matrix<Type, Rows, Columns> :: operator - (const Matrix & m) const {
	Matrix result;
	for(UNSIGNED_TYPE i = 0; i < Rows * Columns; ++i)
		result[i] = (*this).components[i] - m.components[i];
	return result;
}

template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
ms::math::Matrix<Type, Rows, Columns> & ms::math::Matrix<Type, Rows, Columns> :: operator -= (const Matrix & m) {
	for(UNSIGNED_TYPE i = 0; i < Rows * Columns; ++i)
		(*this).components -= m.components[i];
	return (*this);
}

template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
ms::math::Matrix<Type, Rows, Columns> ms::math::Matrix<Type, Rows, Columns> :: operator + (const Matrix & m) const {
	Matrix result;
	for(UNSIGNED_TYPE i = 0; i < Rows * Columns; ++i)
		result[i] = (*this).components[i] + m.components[i];
	return result;
}

template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
ms::math::Matrix<Type, Rows, Columns> & ms::math::Matrix<Type, Rows, Columns> :: operator += (const Matrix & m) {
	for(UNSIGNED_TYPE i = 0; i < Rows * Columns; ++i)
		(*this).components += m.components[i];
	return (*this);
}

//TODO
//Matrix & 		operator *= 		(const Matrix & m);

//TODO
//Matrix	 		operator *	 		(const Matrix & m);

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
Type & ms::math::Matrix<Type, Rows, Columns> :: operator [] (UNSIGNED_TYPE index) {
	return (*this).components[index];
}


//TODO
//std::string 	to_string			() const;

template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
const Type * ms::math::Matrix<Type, Rows, Columns> :: c_array() const {
	return (*this).components;
}

#endif
