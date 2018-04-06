//
//  matrix4f.h
//  glMath
//
//  Created by Mateusz Stompór on 06/04/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#ifndef matrix4f_h
#define matrix4f_h

#include "matrix.h"

namespace ms {

	namespace math {

		template <>
		class Matrix<float, 4, 4> {

		public:

			//static functions


			inline static Matrix 				diagonal			(float value);
			inline static Matrix 				identity			();

		public:
												Matrix				() = default;
			inline 								Matrix				(float value);
			inline 								Matrix				(const Matrix & m);
			inline 								Matrix				(const float array [16]);

			inline Matrix 						operator - 			(const Matrix & m) const;
			inline Matrix & 					operator -= 		(const Matrix & m);

			inline Matrix 						operator + 			(const Matrix & m) const;
			inline Matrix & 					operator += 		(const Matrix & m);

			inline Matrix & 					operator *= 		(const Matrix & m);

			template <UNSIGNED_TYPE C>
			inline Matrix<float, 4, C> 			operator * 			(const Matrix<float, 4, C> &) const;

			inline Vector<float, 4>				operator *			(const Vector<float, 4> & b) const;

			inline Matrix & 					operator *= 		(float value);
			inline Matrix	 					operator *	 		(float value) const;

			inline bool	 						operator ==	 		(const Matrix & m);
			inline bool	 						operator !=	 		(const Matrix & m);

			inline Matrix 						transposition 		() const;

			inline float & 						operator []		(UNSIGNED_TYPE index);

			inline const float & 				operator []			(UNSIGNED_TYPE index) const;

			inline std::string 					to_string			() const;

			inline float *		 				c_array				();

			inline const float * 				c_array				() const;

			float								components[16];

		};

	}

}

ms::math::Matrix<float, 4, 4> ms::math::Matrix<float, 4, 4> :: identity () {
	return diagonal(1.0f);
}


ms::math::Matrix<float, 4, 4> ms::math::Matrix<float, 4, 4> :: diagonal (float value) {
	Matrix m;
	for(UNSIGNED_TYPE row = 0; row < 4; ++row)
		for(UNSIGNED_TYPE column = 0; column < 4; ++column)
			m.components[column * 4 + row] = row == column ? value : 0;
	return m;
}

ms::math::Matrix<float, 4, 4> :: Matrix(float value) {
	for(UNSIGNED_TYPE i = 0; i < 16; ++i)
		(*this).components[i] = value;
}

ms::math::Matrix<float, 4, 4> :: Matrix(const Matrix & m) {
	std::memcpy((*this).components, m.components, sizeof(float) * 16);
}

ms::math::Matrix<float, 4, 4> :: Matrix(const float array [16]) {
	std::memcpy((*this).components, array, sizeof(float) * 16);
}

ms::math::Matrix<float, 4, 4> ms::math::Matrix<float, 4, 4> :: operator - (const Matrix<float, 4, 4> & m) const {
	Matrix result;
	for(UNSIGNED_TYPE i = 0; i < 4 * 4; ++i)
		result[i] = this->components[i] - m.components[i];
	return result;
}

ms::math::Matrix<float, 4, 4> & ms::math::Matrix<float, 4, 4> :: operator -= (const Matrix<float, 4, 4> & m) {
	for(UNSIGNED_TYPE i = 0; i < 16; ++i)
		this->components[i] -= m.components[i];
	return *this;
}

ms::math::Matrix<float, 4, 4> ms::math::Matrix<float, 4, 4> :: operator + (const Matrix & m) const {
	Matrix result;
	for(UNSIGNED_TYPE i = 0; i < 16; ++i)
		result[i] = this->components[i] + m.components[i];
	return result;
}

ms::math::Matrix<float, 4, 4> & ms::math::Matrix<float, 4, 4> :: operator += (const Matrix & m) {
	for(UNSIGNED_TYPE i = 0; i < 16; ++i)
		this->components[i] += m.components[i];
	return *this;
}

ms::math::Matrix<float, 4, 4> & ms::math::Matrix<float, 4, 4> :: operator *= (const Matrix & m) {
	(*this) = (*this) * m;
	return (*this);
}

template <UNSIGNED_TYPE C>
ms::math::Matrix<float, 4, C> ms::math::Matrix<float, 4, 4> :: operator * (const Matrix<float, 4, C> & m) const {
	Matrix <float, 4, C> result;

	for(UNSIGNED_TYPE outerIterator = 0; outerIterator < 4; ++outerIterator)
		for (UNSIGNED_TYPE innerIterator = 0; innerIterator < C; ++innerIterator) {
			result.components[4 * innerIterator + outerIterator] = 0;
			for (UNSIGNED_TYPE i = 0; i < 4; ++i)
				result.components[4 * innerIterator + outerIterator] += this->components[4*i + outerIterator ] * m.components[4*innerIterator + i];
		}

	return result;
}

ms::math::Vector<float, 4> ms::math::Matrix<float, 4, 4> :: operator * (const Vector<float, 4> & v) const {
	Vector<float, 4> result;
	for(UNSIGNED_TYPE row = 0; row < 4; ++row) {
		result.components[row] = 0.0;
		for(UNSIGNED_TYPE column = 0; column < 4; ++column)
			result.components[row] += v.components[column] * this->components[4 * column + row];
	}
	return result;
}

ms::math::Matrix<float, 4, 4> & ms::math::Matrix<float, 4, 4> :: operator *= (float value) {
	for(UNSIGNED_TYPE i = 0; i < 16; ++i)
		this->components[i] *= value;
	return (*this);
}

ms::math::Matrix<float, 4, 4> ms::math::Matrix<float, 4, 4> :: operator * (float value) const {
	Matrix result;
	for(UNSIGNED_TYPE i = 0; i < 16; ++i)
		result[i] = (*this).components[i] * value;
	return result;
}

bool ms::math::Matrix<float, 4, 4> :: operator == (const Matrix & m) {
	return !((*this) != m);
}

bool ms::math::Matrix<float, 4, 4> :: operator != (const Matrix & m) {
	for(UNSIGNED_TYPE i = 0; i < 16; ++i) {
		if (m.components[i] != (*this).components[i])
			return true;
	}
	return false;
}

ms::math::Matrix<float, 4, 4> ms::math::Matrix<float, 4, 4> :: transposition () const {
	Matrix mat;
	for (UNSIGNED_TYPE row = 0; row < 4; ++row)
		for (UNSIGNED_TYPE column = 0; column < 4; ++column)
			mat.components[row * 4 + column] = this->components[row + column * 4];
	return mat;
}

float & ms::math::Matrix<float, 4, 4> :: operator [] (UNSIGNED_TYPE index) {
	return this->components[index];
}

const float & ms::math::Matrix<float, 4, 4> :: operator [] (UNSIGNED_TYPE index) const {
	return this->components[index];
}

std::string ms::math::Matrix<float, 4, 4> :: to_string() const {
	std::ostringstream output;
	for (UNSIGNED_TYPE row = 0; row < 4; ++row) {
		for (UNSIGNED_TYPE column = 0; column < 4; ++column) {
			output << std::setprecision(2) << components[column * 4 + row] << " ";
		}
		output << std::endl;
	}
	return output.str();
}

const float * ms::math::Matrix<float, 4, 4> :: c_array() const {
	return this->components;
}

float * ms::math::Matrix<float, 4, 4> :: c_array() {
	return this->components;
}

#endif /* matrix4f_h */


