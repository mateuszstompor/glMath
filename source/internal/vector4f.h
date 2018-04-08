//
//  vector4f.h
//  glMath
//
//  Created by Mateusz Stompór on 08/04/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#ifndef vector4f_h
#define vector4f_h

#include "vector.h"

namespace ms {
	
	namespace math {
		
		template<>
		class Vector<float, 4> {
			
		public:
			
												Vector				() = default;
			
			inline 								Vector				(const Vector & v);
			inline 								Vector				(const float array [4]);
			inline 								Vector				(float x, float y, float z, float w);
//			inline 								Vector				(const spco::DegreesSpherical<Type> sphericalCoordinates);
//			inline 								Vector				(const spco::RadiansSpherical<Type> sphericalCoordinates);
		
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
			
			inline Vector<float, 5>				expanded			(float value) const;
			
			template <UNSIGNED_TYPE Columns>
			Vector<float, Columns>				operator	*		(const Matrix<float, 4, Columns> &) const;
			
			template <UNSIGNED_TYPE Columns>
			inline Vector<float, Columns> &		operator	*=		(const Matrix<float, 4, Columns> &);
			
			inline float & 						operator 	[] 		(UNSIGNED_TYPE position);
			inline float const & 				operator 	[] 		(UNSIGNED_TYPE position) const;
			
			inline float 						dot					(const Vector & v) const;
//			inline Vector 						cross				(const Vector & v) const;
			
			inline float	 					length				() const;
			inline float	 					length2				() const;
			
			inline void	 						normalize			();
			inline Vector						normalized			() const;
			
			inline std::string 					to_string			() const;
			
			inline float *		 				c_array				();
			inline const float * 				c_array				() const;
			
			inline float const &				x					() const;
			inline float &						x					();
			
			inline float const &				y					() const;
			inline float &						y					();
			
			inline float const &				z					() const;
			inline float &						z					();
			
			inline float const &				w					() const;
			inline float &						w					();
			
			inline Vector<float, 3>				xyz					() const;
			inline Vector<float, 2> 			xy					() const;
			
			float 								components [4];

		};
		
	}
	
}

ms::math::Vector<float, 4>::Vector(const Vector & v) {
	std::memcpy(this->components, v.components, 4 * sizeof(float));
}

ms::math::Vector<float, 4>::Vector(const float array [4]) : Vector() {
	std::memcpy(this->components, array, 4 * sizeof(float));
}

ms::math::Vector<float, 4>::Vector (float x, float y, float z, float w) : components{x, y, z, w} { }

ms::math::Vector<float, 4> & ms::math::Vector<float, 4>::operator=(const Vector & v) {
	std::memcpy((*this).components, v.components, 4 * sizeof(float));
	return *this;
}

//ms::math::Vector<Type, Dimension> :: Vector (const spco::DegreesSpherical <Type> sphericalCoordinates) : Vector( spco::RadiansSpherical <Type> ( sphericalCoordinates ) ) {
//	static_assert(Dimension == 3, "Spherical system requires dimension of three");
//}
//
//
//ms::math::Vector<Type, Dimension> :: Vector (const spco::RadiansSpherical <Type> sphericalCoordinates) : Vector() {
//	static_assert(Dimension == 3, "Spherical system requires dimension of three");
//	(*this).components[0] = sphericalCoordinates.radius * cosine<Type>(sphericalCoordinates.azimuthAngle)	* sinus<Type>(sphericalCoordinates.inclination);
//	(*this).components[1] = sphericalCoordinates.radius * sinus<Type>(sphericalCoordinates.azimuthAngle) 	* sinus<Type>(sphericalCoordinates.inclination);
//	(*this).components[2] = sphericalCoordinates.radius * cosine<Type>(sphericalCoordinates.inclination);
//}
//

bool ms::math::Vector<float, 4>::operator == (const Vector & v) const {
	return v.components[0] == this->components[0] && v.components[1] == this->components[1] && v.components[2] == this->components[2] && v.components[3] == this->components[3];
}


bool ms::math::Vector<float, 4>::operator != (const Vector & v) const {
	return v.components[0] != this->components[0] || v.components[1] != this->components[1] || v.components[2] != this->components[2] || v.components[3] != this->components[3];
}

float ms::math::Vector<float, 4>::dot(const Vector & v) const {
	return 	this->components[0] * v.components[0] +
			this->components[1] * v.components[1] +
			this->components[2] * v.components[2] +
			this->components[3] * v.components[3];
}

//ms::math::Vector<Type, Dimension> ms::math::Vector<Type, Dimension>::cross(const Vector & v) const {
//	static_assert(Dimension == 3, "Cross product exists only for dimension of three");
//	Vector vec;
//	vec[0] = this->components[1] * v.components[2] - this->components[2] * v.components[1];
//	vec[1] = this->components[2] * v.components[0] - this->components[0] * v.components[2];
//	vec[2] = this->components[0] * v.components[1] - this->components[1] * v.components[0];
//	return vec;
//}

ms::math::Vector<float, 4> & ms::math::Vector<float, 4>::operator /= (float value) {
	this->components[0] /= value;
	this->components[1] /= value;
	this->components[2] /= value;
	this->components[3] /= value;
	return *this;
}


ms::math::Vector<float, 4> ms::math::Vector<float, 4>::operator / (float value) const {
	return Vector(this->components[0] / value, this->components[1] / value, this->components[2] / value, this->components[3] / value);
}

ms::math::Vector<float, 4> & ms::math::Vector<float, 4>::operator *= (float value) {
	this->components[0] *= value;
	this->components[1] *= value;
	this->components[2] *= value;
	this->components[3] *= value;
	return *this;
}


ms::math::Vector<float, 4> ms::math::Vector<float, 4>::operator * (float value) const {
	return Vector(this->components[0] * value, this->components[1] * value, this->components[2] * value, this->components[3] * value);
}

template <UNSIGNED_TYPE Columns>
ms::math::Vector<float, Columns> ms::math::Vector<float, 4> :: operator * (const Matrix<float, 4, Columns> & m) const {
	Vector<float, Columns> result;
	for(UNSIGNED_TYPE row = 0; row < 4; ++row) {
		result.components[row] = 0.0;
		for(UNSIGNED_TYPE column = 0; column < Columns; ++column)
			result.components[row] += (*this).components[column] * m.components[4 * column + row];
	}
	return result;
}


template <UNSIGNED_TYPE Columns>
ms::math::Vector<float, Columns> & ms::math::Vector<float, 4> :: operator *= (const Matrix<float, 4, Columns> & m) {
	Vector<float, Columns> result;
	result = (*this) * m;
	(*this) = result;
	return (*this);
}

float& ms::math::Vector<float, 4>::operator [] (UNSIGNED_TYPE position) {
	return components[position];
}

const float& ms::math::Vector<float, 4>::operator [] (UNSIGNED_TYPE position) const {
	return components[position];
}

ms::math::Vector<float, 4> ms::math::Vector<float, 4>::operator + (const Vector & v) const {
	return ms::math::Vector<float, 4>(v.components[0] + this->components[0],
									  v.components[1] + this->components[1],
									  v.components[2] + this->components[2],
									  v.components[3] + this->components[3]);
}

ms::math::Vector<float, 4> ms::math::Vector<float, 4>::operator - (const Vector & v) const {
	return ms::math::Vector<float, 4>(v.components[0] - this->components[0],
									  v.components[1] - this->components[1],
									  v.components[2] - this->components[2],
									  v.components[3] - this->components[3]);
}

ms::math::Vector<float, 4> & ms::math::Vector<float, 4>::operator += (const Vector & v) {
	this->components[0] += v.components[0];
	this->components[1] += v.components[1];
	this->components[2] += v.components[2];
	this->components[3] += v.components[3];
	return *this;

}

ms::math::Vector<float, 4> & ms::math::Vector<float, 4>::operator -= (const Vector & v) {
	this->components[0] -= v.components[0];
	this->components[1] -= v.components[1];
	this->components[2] -= v.components[2];
	this->components[3] -= v.components[3];
	return *this;
}

float ms::math::Vector<float, 4>::length() const {
	return ms::math::square_root<float>(components[0] * components[0] + components[1] * components[1] + components[2] * components[2] + components[3] * components[3]);
}


float ms::math::Vector<float, 4>::length2() const {
	return components[0] * components[0] + components[1] * components[1] + components[2] * components[2] + components[3] * components[3];
}

void ms::math::Vector<float, 4>::normalize() {
	float len = components[0] * components[0] + components[1] * components[1] + components[2] * components[2] + components[3] * components[3];
	components[0] /= len;
	components[1] /= len;
	components[2] /= len;
	components[3] /= len;
}

ms::math::Vector<float, 4> ms::math::Vector<float, 4> :: normalized() const {
	float len = components[0] * components[0] + components[1] * components[1] + components[2] * components[2] + components[3] * components[3];
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

const float * ms::math::Vector<float, 4>::c_array() const {
	return components;
}

float * ms::math::Vector<float, 4>::c_array() {
	return components;
}

float const & ms::math::Vector <float, 4>::x () const {
	return *this->components;
}

float & ms::math::Vector <float, 4>::x () {
	return *this->components;
}

float const & ms::math::Vector <float, 4>::y () const {
	return *(this->components + 1);
}

float & ms::math::Vector <float, 4>::y () {
	return *(this->components + 1);
}

float const & ms::math::Vector <float, 4>::z () const  {
	return *(this->components + 2);
}

float & ms::math::Vector <float, 4>::z ()  {
	return *(this->components + 2);
}

float const & ms::math::Vector <float, 4>::w () const  {
	return *(this->components + 3);
}


float & ms::math::Vector <float, 4>::w () {
	return *(this->components + 3);
}

ms::math::Vector <float, 3> ms::math::Vector <float, 4>::xyz () const {
	return Vector <float, 3>{this->x(), this->y(), this->z()};
}

ms::math::Vector <float, 2> ms::math::Vector <float, 4>::xy () const {
	return Vector <float, 2>{this->x(), this->y()};
}

ms::math::Vector<float, 5> ms::math::Vector<float, 4>::expanded (float value) const {
	return Vector<float, 5>(components[0], components[1], components[2], components[3], value);
}

#endif /* vector4f_h */
