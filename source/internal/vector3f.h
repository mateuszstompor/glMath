//
//  vector3f.h
//  glMath
//
//  Created by Mateusz Stompór on 08/04/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#ifndef vector3f_h
#define vector3f_h

#include "vector.h"
#include "sc_degrees.h"
#include "sc_radians.h"

namespace ms {

	namespace math {

		template<>
		class Vector<float, 3> {

		public:

												Vector				() = default;

			inline 								Vector				(const Vector & v);
			inline 								Vector				(const float array [3]);
			inline 								Vector				(float x, float y, float z);
			inline 								Vector				(const spco::DegreesSpherical<float> sphericalCoordinates);
			inline 								Vector				(const spco::RadiansSpherical<float> sphericalCoordinates);

												~Vector() = default;

			inline Vector &						operator	=		(const Vector & v);

			inline bool							operator	==		(const Vector & v) const;
			inline bool							operator	!=		(const Vector & v) const;
			inline Vector						operator	+		(const Vector & v) const;
			inline Vector & 					operator 	+= 		(const Vector & v);
			inline Vector 						operator 	- 		(const Vector & v) const;
			inline Vector & 					operator 	-= 		(const Vector & v);

			inline Vector 						operator 	/ 		(float value) const;
			inline Vector& 						operator 	/= 		(float value);

			inline Vector 						operator 	* 		(float value) const;
			inline Vector& 						operator 	*= 		(float value);

			template <UNSIGNED_TYPE Columns>
			Vector<float, Columns>				operator	*		(const Matrix<float, 3, Columns> &) const;

			template <UNSIGNED_TYPE Columns>
			inline Vector<float, Columns> &		operator	*=		(const Matrix<float, 3, Columns> &);

			inline constexpr float & 			operator 	[] 		(UNSIGNED_TYPE position);
			inline constexpr float const & 		operator 	[] 		(UNSIGNED_TYPE position) const;

			inline float 						dot					(const Vector & v) const;
			inline Vector 						cross				(const Vector & v) const;

			inline float	 					length				() const;
			inline float	 					length2				() const;

			inline Vector &	 					normalize			();
			inline Vector						normalized			() const;

			inline std::string 					to_string			() const;

			inline constexpr float *		 	c_array				();
			inline constexpr const float * 		c_array				() const;

			inline constexpr float const &		x					() const;
			inline constexpr float &			x					();

			inline constexpr float const &		y					() const;
			inline constexpr float &			y					();

			inline constexpr float const &		z					() const;
			inline constexpr float &			z					();

			inline Vector<float, 2> 			xy					() const;

			float 								components [3];

		};

	}

}

ms::math::Vector<float, 3>::Vector(const Vector & v) {
	std::memcpy(this->components, v.components, 3 * sizeof(float));
}

ms::math::Vector<float, 3>::Vector(const float array [3]) : Vector() {
	std::memcpy(this->components, array, 3 * sizeof(float));
}

ms::math::Vector<float, 3>::Vector (float x, float y, float z) : components{x, y, z} { }

ms::math::Vector<float, 3> & ms::math::Vector<float, 3>::operator = (const Vector & v) {
	std::memcpy(this->components, v.components, 3 * sizeof(float));
	return *this;
}

ms::math::Vector<float, 3> :: Vector (const spco::DegreesSpherical <float> sphericalCoordinates) : Vector( spco::RadiansSpherical <float> ( sphericalCoordinates ) ) { }


ms::math::Vector<float, 3> :: Vector (const spco::RadiansSpherical <float> sphericalCoordinates) {
	(*this).components[0] = sphericalCoordinates.radius * cosine<float>(sphericalCoordinates.azimuthAngle)	* sinus<float>(sphericalCoordinates.inclination);
	(*this).components[1] = sphericalCoordinates.radius * sinus<float>(sphericalCoordinates.azimuthAngle) 	* sinus<float>(sphericalCoordinates.inclination);
	(*this).components[2] = sphericalCoordinates.radius * cosine<float>(sphericalCoordinates.inclination);
}

bool ms::math::Vector<float, 3>::operator == (const Vector & v) const {
	return v.components[0] == this->components[0] && v.components[1] == this->components[1] && v.components[2] == this->components[2];
}


bool ms::math::Vector<float, 3>::operator != (const Vector & v) const {
	return v.components[0] != this->components[0] || v.components[1] != this->components[1] || v.components[2] != this->components[2];
}

float ms::math::Vector<float, 3>::dot(const Vector & v) const {
	return 	this->components[0] * v.components[0] +
			this->components[1] * v.components[1] +
			this->components[2] * v.components[2];
}

ms::math::Vector<float, 3> ms::math::Vector<float, 3>::cross(const Vector & v) const {
	return Vector(this->components[1] * v.components[2] - this->components[2] * v.components[1],
				  this->components[2] * v.components[0] - this->components[0] * v.components[2],
				  this->components[0] * v.components[1] - this->components[1] * v.components[0]);
}

ms::math::Vector<float, 3> & ms::math::Vector<float, 3>::operator /= (float value) {
	this->components[0] /= value;
	this->components[1] /= value;
	this->components[2] /= value;
	return *this;
}

ms::math::Vector<float, 3> ms::math::Vector<float, 3>::operator / (float value) const {
	return Vector(this->components[0] / value, this->components[1] / value, this->components[2] / value);
}

ms::math::Vector<float, 3> & ms::math::Vector<float, 3>::operator *= (float value) {
	this->components[0] *= value;
	this->components[1] *= value;
	this->components[2] *= value;
	return *this;
}

ms::math::Vector<float, 3> ms::math::Vector<float, 3>::operator * (float value) const {
	return Vector(this->components[0] * value, this->components[1] * value, this->components[2] * value);
}

template <UNSIGNED_TYPE Columns>
ms::math::Vector<float, Columns> ms::math::Vector<float, 3> :: operator * (const Matrix<float, 3, Columns> & m) const {
	Vector<float, Columns> result;
	for(UNSIGNED_TYPE row = 0; row < 3; ++row) {
		result.components[row] = 0.0;
		for(UNSIGNED_TYPE column = 0; column < Columns; ++column)
			result.components[row] += (*this).components[column] * m.components[3 * column + row];
	}
	return result;
}

template <UNSIGNED_TYPE Columns>
ms::math::Vector<float, Columns> & ms::math::Vector<float, 3> :: operator *= (const Matrix<float, 3, Columns> & m) {
	Vector<float, Columns> result;
	result = (*this) * m;
	(*this) = result;
	return (*this);
}

constexpr float& ms::math::Vector<float, 3>::operator [] (UNSIGNED_TYPE position) {
	return components[position];
}

constexpr const float& ms::math::Vector<float, 3>::operator [] (UNSIGNED_TYPE position) const {
	return components[position];
}

ms::math::Vector<float, 3> ms::math::Vector<float, 3>::operator + (const Vector & v) const {
	return ms::math::Vector<float, 3>(v.components[0] + this->components[0],
									  v.components[1] + this->components[1],
									  v.components[2] + this->components[2]);
}

ms::math::Vector<float, 3> ms::math::Vector<float, 3>::operator - (const Vector & v) const {
	return ms::math::Vector<float, 3>(this->components[0] - v.components[0],
									  this->components[1] - v.components[1],
									  this->components[2] - v.components[2]);
}

ms::math::Vector<float, 3> & ms::math::Vector<float, 3>::operator += (const Vector & v) {
	this->components[0] += v.components[0];
	this->components[1] += v.components[1];
	this->components[2] += v.components[2];
	return *this;

}

ms::math::Vector<float, 3> & ms::math::Vector<float, 3>::operator -= (const Vector & v) {
	this->components[0] -= v.components[0];
	this->components[1] -= v.components[1];
	this->components[2] -= v.components[2];
	return *this;
}

float ms::math::Vector<float, 3>::length() const {
	return ms::math::square_root<float>(components[0] * components[0] + components[1] * components[1] + components[2] * components[2]);
}


float ms::math::Vector<float, 3>::length2() const {
	return components[0] * components[0] + components[1] * components[1] + components[2] * components[2];
}

ms::math::Vector<float, 3> & ms::math::Vector<float, 3>::normalize() {
	float len = ms::math::square_root<float>(components[0] * components[0] + components[1] * components[1] + components[2] * components[2]);
	components[0] /= len;
	components[1] /= len;
	components[2] /= len;
	return *this;
}

ms::math::Vector<float, 3> ms::math::Vector<float, 3> :: normalized() const {
	float len = ms::math::square_root<float>(components[0] * components[0] + components[1] * components[1] + components[2] * components[2]);
	return Vector(components[0]/len, components[1]/len, components[2]/len);
}

std::string ms::math::Vector<float, 3>::to_string() const {
	std::ostringstream output;

	output << components[0] << " ";
	output << components[1] << " ";
	output << components[2] << " ";

	return output.str();
}

constexpr const float * ms::math::Vector<float, 3>::c_array() const {
	return this->components;
}

constexpr float * ms::math::Vector<float, 3>::c_array() {
	return this->components;
}

constexpr float const & ms::math::Vector <float, 3>::x () const {
	return *this->components;
}

constexpr float & ms::math::Vector <float, 3>::x () {
	return *this->components;
}

constexpr float const & ms::math::Vector <float, 3>::y () const {
	return *(this->components + 1);
}

constexpr float & ms::math::Vector <float, 3>::y () {
	return *(this->components + 1);
}

constexpr float const & ms::math::Vector <float, 3>::z () const  {
	return *(this->components + 2);
}

constexpr float & ms::math::Vector <float, 3>::z ()  {
	return *(this->components + 2);
}

ms::math::Vector <float, 2> ms::math::Vector <float, 3>::xy () const {
	return Vector <float, 2>{this->components[0], this->components[1]};
}

#endif /* vector3f_h */

















