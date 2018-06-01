//
//  matrix3f.h
//  glMath
//
//  Created by Mateusz Stompór on 08/04/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#pragma once

#include "matrix.h"

namespace ms {
	
	namespace math {
		
		template <>
		class Matrix<float, 3, 3> {
			
		public:
			
			//static functions
			
			inline static Matrix 				diagonal			(float value);
			inline static Matrix 				identity			();
			
		public:
			Matrix				() = default;
			inline 								Matrix				(float value);
			inline 								Matrix				(const Matrix & m);
			inline 								Matrix				(const float array [9]);
			
			inline Matrix 						operator - 			(const Matrix & m) const;
			inline Matrix & 					operator -= 		(const Matrix & m);
			
			inline Matrix 						operator + 			(const Matrix & m) const;
			inline Matrix & 					operator += 		(const Matrix & m);
			
			inline Matrix & 					operator *= 		(const Matrix & m);
			inline Matrix &						operator =			(const Matrix & m);
			
			template <UNSIGNED_TYPE C>
			inline Matrix<float, 3, C> 			operator * 			(const Matrix<float, 3, C> &) const;
			
			inline Matrix<float, 3, 3> 			operator * 			(const Matrix<float, 3, 3> & m) const;
			
			inline Vector<float, 3>				operator *			(const Vector<float, 3> & b) const;
			
			inline Matrix & 					operator *= 		(float value);
			inline Matrix	 					operator *	 		(float value) const;
			
			inline bool	 						operator ==	 		(const Matrix & m);
			inline bool	 						operator !=	 		(const Matrix & m);
			
			inline Matrix 						transposition 		() const;
			
			inline constexpr float & 			operator []			(UNSIGNED_TYPE index);
			
			inline constexpr const float & 		operator []			(UNSIGNED_TYPE index) const;
			
			inline std::string 					to_string			() const;
			
			inline constexpr float *		 	c_array				();
			
			inline constexpr const float * 		c_array				() const;
			
			float								components[9];
			
		};
		
	}
	
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
	std::memcpy(this->components, m.components, sizeof(float) * 9);
}

ms::math::Matrix<float, 3, 3> :: Matrix(const float array [9]) {
	std::memcpy(this->components, array, sizeof(float) * 9);
}

ms::math::Matrix<float, 3, 3> ms::math::Matrix<float, 3, 3> :: operator - (const Matrix<float, 3, 3> & m) const {
	Matrix result;
	
	result.components[0] = this->components[0] - m.components[0];
	result.components[1] = this->components[1] - m.components[1];
	result.components[2] = this->components[2] - m.components[2];
	result.components[3] = this->components[3] - m.components[3];
	result.components[4] = this->components[4] - m.components[4];
	result.components[5] = this->components[5] - m.components[5];
	result.components[6] = this->components[6] - m.components[6];
	result.components[7] = this->components[7] - m.components[7];
	result.components[8] = this->components[8] - m.components[8];
	
	return result;
}

ms::math::Matrix<float, 3, 3> & ms::math::Matrix<float, 3, 3> :: operator -= (const Matrix<float, 3, 3> & m) {
	this->components[0] -= m.components[0];
	this->components[1] -= m.components[1];
	this->components[2] -= m.components[2];
	this->components[3] -= m.components[3];
	this->components[4] -= m.components[4];
	this->components[5] -= m.components[5];
	this->components[6] -= m.components[6];
	this->components[7] -= m.components[7];
	this->components[8] -= m.components[8];
	return *this;
}

ms::math::Matrix<float, 3, 3> ms::math::Matrix<float, 3, 3> :: operator + (const Matrix & m) const {
	Matrix result;
	
	result.components[0] = this->components[0] + m.components[0];
	result.components[1] = this->components[1] + m.components[1];
	result.components[2] = this->components[2] + m.components[2];
	result.components[3] = this->components[3] + m.components[3];
	result.components[4] = this->components[4] + m.components[4];
	result.components[5] = this->components[5] + m.components[5];
	result.components[6] = this->components[6] + m.components[6];
	result.components[7] = this->components[7] + m.components[7];
	result.components[8] = this->components[8] + m.components[8];
	
	return result;
}

ms::math::Matrix<float, 3, 3> & ms::math::Matrix<float, 3, 3> :: operator += (const Matrix & m) {
	
	this->components[0] += m.components[0];
	this->components[1] += m.components[1];
	this->components[2] += m.components[2];
	this->components[3] += m.components[3];
	this->components[4] += m.components[4];
	this->components[5] += m.components[5];
	this->components[6] += m.components[6];
	this->components[7] += m.components[7];
	this->components[8] += m.components[8];
	
	return *this;
}

ms::math::Matrix<float, 3, 3> & ms::math::Matrix<float, 3, 3> :: operator *= (const Matrix & m) {
	(*this) = (*this) * m;
	return (*this);
}

template <UNSIGNED_TYPE C>
ms::math::Matrix<float, 3, C> ms::math::Matrix<float, 3, 3> :: operator * (const Matrix<float, 3, C> & m) const {
	Matrix <float, 3, C> result;
	
	for(UNSIGNED_TYPE outerIterator = 0; outerIterator < 3; ++outerIterator)
		for (UNSIGNED_TYPE innerIterator = 0; innerIterator < C; ++innerIterator) {
			result.components[3 * innerIterator + outerIterator] = 0;
			for (UNSIGNED_TYPE i = 0; i < 3; ++i)
				result.components[3 * innerIterator + outerIterator] += this->components[3*i + outerIterator ] * m.components[3*innerIterator + i];
		}
	
	return result;
}

ms::math::Matrix<float, 3, 3> & ms::math::Matrix<float, 3, 3>::operator = (const Matrix & m) {
	std::memcpy(this->components, m.components, sizeof(float) * 9);
	return *this;
}

ms::math::Vector<float, 3> ms::math::Matrix<float, 3, 3> :: operator * (const Vector<float, 3> & v) const {
	return Vector<float, 3>(v.components[0] * this->components[0] +
							v.components[1] * this->components[3] +
							v.components[2] * this->components[6],
							v.components[0] * this->components[1] +
							v.components[1] * this->components[4] +
							v.components[2] * this->components[7],
							v.components[0] * this->components[2] +
							v.components[1] * this->components[5] +
							v.components[2] * this->components[8]);
}

ms::math::Matrix<float, 3, 3> & ms::math::Matrix<float, 3, 3> :: operator *= (float value) {
	
	this->components[0] *= value;
	this->components[1] *= value;
	this->components[2] *= value;
	this->components[3] *= value;
	this->components[4] *= value;
	this->components[5] *= value;
	this->components[6] *= value;
	this->components[7] *= value;
	this->components[8] *= value;
	
	return (*this);
}

ms::math::Matrix<float, 3, 3> ms::math::Matrix<float, 3, 3> :: operator * (float value) const {
	Matrix result;
	
	result.components[0] 	= (*this).components[0] * value;
	result.components[1] 	= (*this).components[1] * value;
	result.components[2] 	= (*this).components[2] * value;
	result.components[3] 	= (*this).components[3] * value;
	result.components[4] 	= (*this).components[4] * value;
	result.components[5] 	= (*this).components[5] * value;
	result.components[6] 	= (*this).components[6] * value;
	result.components[7] 	= (*this).components[7] * value;
	result.components[8] 	= (*this).components[8] * value;
	
	return result;
}

bool ms::math::Matrix<float, 3, 3> :: operator == (const Matrix & m) {
	return !((*this) != m);
}

bool ms::math::Matrix<float, 3, 3> :: operator != (const Matrix & m) {
	for(UNSIGNED_TYPE i = 0; i < 9; ++i) {
		if (m.components[i] != (*this).components[i])
			return true;
	}
	return false;
}

ms::math::Matrix<float, 3, 3> ms::math::Matrix<float, 3, 3> :: transposition () const {
	Matrix mat;
	for (UNSIGNED_TYPE row = 0; row < 3; ++row)
		for (UNSIGNED_TYPE column = 0; column < 3; ++column)
			mat.components[row * 3 + column] = this->components[row + column * 3];
	return mat;
}

constexpr float & ms::math::Matrix<float, 3, 3> :: operator [] (UNSIGNED_TYPE index) {
	return this->components[index];
}

constexpr const float & ms::math::Matrix<float, 3, 3> :: operator [] (UNSIGNED_TYPE index) const {
	return this->components[index];
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
	return this->components;
}

constexpr float * ms::math::Matrix<float, 3, 3> :: c_array() {
	return this->components;
}

ms::math::Matrix<float, 3, 3> ms::math::Matrix<float, 3, 3> ::operator * (const Matrix<float, 3, 3> & m) const {
	Matrix <float, 3, 3> result;
	
	result.components[0] =
	this->components[0 ] * m.components[0] +
	this->components[3] * m.components[1] +
	this->components[6] * m.components[2];
	
	result.components[3] =
	this->components[0] * m.components[3] +
	this->components[3] * m.components[4] +
	this->components[6] * m.components[5];
	
	result.components[6] =
	this->components[0] * m.components[6] +
	this->components[3] * m.components[7] +
	this->components[6] * m.components[8];
	
	result.components[1] =
	this->components[1] * m.components[0] +
	this->components[4] * m.components[1] +
	this->components[7] * m.components[2];
	
	result.components[4] =
	this->components[1] * m.components[3] +
	this->components[4] * m.components[4] +
	this->components[7] * m.components[5];
	
	result.components[7] =
	this->components[1] * m.components[6] +
	this->components[4] * m.components[7] +
	this->components[7] * m.components[8];
	
	result.components[2] =
	this->components[2] * m.components[0] +
	this->components[5] * m.components[1] +
	this->components[8] * m.components[2];
	
	result.components[5] =
	this->components[2] * m.components[3] +
	this->components[5] * m.components[4] +
	this->components[8] * m.components[5];
	
	result.components[8] =
	this->components[2] * m.components[6] +
	this->components[5] * m.components[7] +
	this->components[8] * m.components[8];
	
	return result;
}
