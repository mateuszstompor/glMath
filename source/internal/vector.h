//
//  vector.h
//  glMath
//
//  Created by Mateusz Stompór on 22/02/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#ifndef vector_h
#define vector_h

#include <string>
#include <sstream>
#include <cstring>

#ifdef DEBUG

	#include <cassert>

#endif

#include "common.h"

namespace ms {
    
	namespace math {
		
		namespace spco {
			
			template <typename Type>
			struct DegreesSpherical;
			
			template <typename Type>
			struct RadiansSpherical;
		
		}
		
		template <typename Type, UNSIGNED_TYPE Dimension>
		class Vector {
		
		template <typename T, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
		friend class Matrix;
			
		public:
			
									Vector				();
									Vector				(Type value);
									Vector				(Vector && v);
									Vector				(const Vector & v);
									Vector				(const Type array [Dimension]);
									Vector				(const std::initializer_list<Type> components);
									Vector				(const spco::DegreesSpherical<Type> sphericalCoordinates);
									Vector				(const spco::RadiansSpherical<Type> sphericalCoordinates);
			
									~Vector();
			
			Vector &				operator	=		(const Vector & v);
			Vector &				operator	=		(Vector && v);
			bool					operator	==		(const Vector & v) const;
			bool					operator	!=		(const Vector & v) const;
			Vector					operator	+		(const Vector & v) const;
			Vector & 				operator 	+= 		(const Vector & v);
			Vector 					operator 	- 		(const Vector & v) const;
			Vector & 				operator 	-= 		(const Vector & v);
			
			Vector 					operator 	* 		(float value) const;
			Vector& 				operator 	*= 		(float value);
			
			template <UNSIGNED_TYPE Columns>
			Vector<Type, Columns>	operator	*		(const Matrix<Type, Dimension, Columns>) const;
			
			template <UNSIGNED_TYPE Columns>
			Vector<Type, Columns> &	operator	*=		(const Matrix<Type, Dimension, Columns>);
			
			Type & 					operator 	[] 		(UNSIGNED_TYPE position);
			Type const & 			operator 	[] 		(UNSIGNED_TYPE position) const;
			
			Type 					dot					(const Vector & v) const;
			Vector 					cross				(const Vector & v) const;
			
			Type	 				length				() const;
			
			void	 				normalize			();
			Vector					normalized			() const;
			
			std::string 			to_string			() const;
			
			Type *		 			c_array				();
			const Type * 			c_array				() const;
			
			Type const &			x					() const;
			Type &					x					();
			
			Type const &			y					() const;
			Type &					y					();
			
			Type const &			z					() const;
			Type &					z					();
			
			Type const &			w					() const;
			Type &					w					();
			
		private:
			
			Type * 					components;
			
		};
		
	}
    
}

template <typename Type, UNSIGNED_TYPE Dimension>
ms::math::Vector<Type, Dimension>::Vector() : components( new Type[Dimension] ) { }

template <typename Type, UNSIGNED_TYPE Dimension>
ms::math::Vector<Type, Dimension>::Vector(Type value) : Vector() {
	std::fill_n((*this).components, Dimension, value);
}

template <typename Type, UNSIGNED_TYPE Dimension>
ms::math::Vector<Type, Dimension>::Vector(Vector && v) : components(v.components) {
    v.components = nullptr;
}

template <typename Type, UNSIGNED_TYPE Dimension>
ms::math::Vector<Type, Dimension>::Vector(const Vector & v) : components( new Type[Dimension] ) {
    std::memcpy((*this).components, v.components, Dimension * sizeof(Type));
}

template <typename Type, UNSIGNED_TYPE Dimension>
ms::math::Vector<Type, Dimension>::Vector(const Type array [Dimension]) : components( new Type[Dimension] ) {
	std::memcpy((*this).components, array, Dimension * sizeof(Type));
}

template <typename Type, UNSIGNED_TYPE Dimension>
ms::math::Vector<Type, Dimension>::Vector (const std::initializer_list<Type> comp) : Vector() {

#ifdef DEBUG
	
	assert(comp.size() == Dimension);
	
#endif
	
	std::copy(comp.begin(), comp.end(), components);

}


template <typename Type, UNSIGNED_TYPE Dimension>
ms::math::Vector<Type, Dimension>& ms::math::Vector<Type, Dimension>::operator=(const Vector & v) {
    std::memcpy((*this).components, v.components, Dimension * sizeof(Type));
    return *this;
}

template <typename Type, UNSIGNED_TYPE Dimension>
ms::math::Vector<Type, Dimension>& ms::math::Vector<Type, Dimension>::operator=(Vector && v) {
    delete [] (*this).components;
    
    (*this).components = v.components;
    v.components = nullptr;
    
    return *this;
}

template <typename Type, UNSIGNED_TYPE Dimension>
ms::math::Vector<Type, Dimension> :: Vector (const spco::DegreesSpherical <Type> sphericalCoordinates) : Vector( spco::RadiansSpherical <Type> ( sphericalCoordinates ) ) {
	static_assert(Dimension == 3, "Spherical system requires dimension of three");
}

template <typename Type, UNSIGNED_TYPE Dimension>
ms::math::Vector<Type, Dimension> :: Vector (const spco::RadiansSpherical <Type> sphericalCoordinates) : components( new Type[Dimension] ) {
	static_assert(Dimension == 3, "Spherical system requires dimension of three");
	(*this).components[0] = sphericalCoordinates.radius * cosine<Type>(sphericalCoordinates.azimuthAngle)	* sinus<Type>(sphericalCoordinates.inclination);
	(*this).components[1] = sphericalCoordinates.radius * sinus<Type>(sphericalCoordinates.azimuthAngle) 	* sinus<Type>(sphericalCoordinates.inclination);
	(*this).components[2] = sphericalCoordinates.radius * cosine<Type>(sphericalCoordinates.inclination);
}

template <typename Type, UNSIGNED_TYPE Dimension>
ms::math::Vector<Type, Dimension>::~Vector() {
    delete [] this->components;
}

template <typename Type, UNSIGNED_TYPE Dimension>
bool ms::math::Vector<Type, Dimension>::operator == (const Vector & v) const {
    for(UNSIGNED_TYPE i = 0; i < Dimension; ++i)
        if (v.components[i] != (*this).components[i])
            return false;
    return true;
}

template <typename Type, UNSIGNED_TYPE Dimension>
bool ms::math::Vector<Type, Dimension>::operator != (const Vector & v) const {
    return !( *this == v );
}

template <typename Type, UNSIGNED_TYPE Dimension>
Type ms::math::Vector<Type, Dimension>::dot(const Vector & v) const {
    Type dotProduct = Type(0.0);
    
    for(UNSIGNED_TYPE i = 0; i < Dimension; ++i)
        dotProduct += (*this).components[i] * v.components[i];
    
    return dotProduct;
}

template <typename Type, UNSIGNED_TYPE Dimension>
ms::math::Vector<Type, Dimension> ms::math::Vector<Type, Dimension>::cross(const Vector & v) const {
	static_assert(Dimension == 3, "Cross product exists only for dimension of three");
	Vector vec;
	vec[0] = this->components[1] * v.components[2] - this->components[2] * v.components[1];
	vec[1] = this->components[2] * v.components[0] - this->components[0] * v.components[2];
	vec[2] = this->components[0] * v.components[1] - this->components[1] * v.components[0];
	return vec;
}

template <typename Type, UNSIGNED_TYPE Dimension>
ms::math::Vector<Type, Dimension> & ms::math::Vector<Type, Dimension>::operator *= (float value) {
    
    for(UNSIGNED_TYPE i = 0; i < Dimension; ++i)
        (*this).components[i] *= value;
    
    return *this;
    
}

template <typename Type, UNSIGNED_TYPE Dimension>
ms::math::Vector<Type, Dimension> ms::math::Vector<Type, Dimension>::operator * (float value) const {
    
    Vector vec;
    
    for(UNSIGNED_TYPE i = 0; i < Dimension; ++i)
        vec.components[i] = (*this).components[i] * value;
    
    return vec;
    
}

template <typename Type, UNSIGNED_TYPE Dimension>
template <UNSIGNED_TYPE Columns>
ms::math::Vector<Type, Columns> ms::math::Vector<Type, Dimension> :: operator * (const Matrix<Type, Dimension, Columns> m) const {
	Vector<Type, Columns> result;
	for(UNSIGNED_TYPE row = 0; row < Dimension; ++row) {
		Type sum = 0.0;
		for(UNSIGNED_TYPE column = 0; column < Columns; ++column)
			sum += (*this).components[column] * m[Dimension * column + row];
		result[row] = sum;
	}
	return result;
}

template <typename Type, UNSIGNED_TYPE Dimension>
template <UNSIGNED_TYPE Columns>
ms::math::Vector<Type, Columns> & ms::math::Vector<Type, Dimension> :: operator *= (const Matrix<Type, Dimension, Columns> m) {
	Vector<Type, Columns> result;
	result = (*this) * m;
	(*this) = result;
	return (*this);
}

template <typename Type, UNSIGNED_TYPE Dimension>
Type& ms::math::Vector<Type, Dimension>::operator [] (UNSIGNED_TYPE position) {
    return (*this).components[position];
}

template <typename Type, UNSIGNED_TYPE Dimension>
const Type& ms::math::Vector<Type, Dimension>::operator [] (UNSIGNED_TYPE position) const {
	return (*this).components[position];
}

template <typename Type, UNSIGNED_TYPE Dimension>
ms::math::Vector<Type, Dimension> operator * (float value, const ms::math::Vector<Type, Dimension> & v) {
    ms::math::Vector<Type, Dimension> vec(v);
    return vec * value;
}

template <typename Type, UNSIGNED_TYPE Dimension>
ms::math::Vector<Type, Dimension> ms::math::Vector<Type, Dimension>::operator + (const Vector & v) const {
    Vector vec;
    
    for(UNSIGNED_TYPE i = 0; i < Dimension; ++i)
        vec.components[i] = (*this).components[i] + v.components[i];
    
    return vec;
}

template <typename Type, UNSIGNED_TYPE Dimension>
ms::math::Vector<Type, Dimension> ms::math::Vector<Type, Dimension>::operator - (const Vector & v) const {
    Vector vec;
    
    for(UNSIGNED_TYPE i = 0; i < Dimension; ++i)
        vec.components[i] = (*this).components[i] - v.components[i];
    
    return vec;
}

template <typename Type, UNSIGNED_TYPE Dimension>
ms::math::Vector<Type, Dimension> & ms::math::Vector<Type, Dimension>::operator += (const Vector & v) {
    
    for(UNSIGNED_TYPE i = 0; i < Dimension; ++i)
        (*this).components[i] += v.components[i];
    
    return *this;
    
}

template <typename Type, UNSIGNED_TYPE Dimension>
ms::math::Vector<Type, Dimension> & ms::math::Vector<Type, Dimension>::operator -= (const Vector & v) {
    
    for(UNSIGNED_TYPE i = 0; i < Dimension; ++i)
        (*this).components[i] -= v.components[i];
    
    return *this;
    
}

template <typename Type, UNSIGNED_TYPE Dimension>
Type ms::math::Vector<Type, Dimension>::length() const {
    Type length = 0.0;
    
    for(UNSIGNED_TYPE i = 0; i < Dimension; ++i)
        length += (*this).components[i] * (*this).components[i];
    
	return ms::math::square_root<Type>(length);
}

template <typename Type, UNSIGNED_TYPE Dimension>
void ms::math::Vector<Type, Dimension>::normalize() {
	float len = length();
	for(UNSIGNED_TYPE i = 0; i < Dimension; ++i)
		components[i] /= len;
}

template <typename Type, UNSIGNED_TYPE Dimension>
ms::math::Vector<Type, Dimension> ms::math::Vector<Type, Dimension> :: normalized() const {
	Vector vec(*this);
	vec.normalize();
	return vec;
}

template <typename Type, UNSIGNED_TYPE Dimension>
std::string ms::math::Vector<Type, Dimension>::to_string() const {
    std::ostringstream output;
    
    for (UNSIGNED_TYPE i = 0; i < Dimension; ++i)
        output << components[i] << " ";
    
    return output.str();
}

template <typename Type, UNSIGNED_TYPE Dimension>
const Type * ms::math::Vector<Type, Dimension>::c_array() const {
    return components;
}

template <typename Type, UNSIGNED_TYPE Dimension>
Type * ms::math::Vector<Type, Dimension>::c_array() {
	return components;
}

template <typename Type, UNSIGNED_TYPE Dimension>
Type const & ms::math::Vector<Type, Dimension>::x () const {
	static_assert(Dimension > 0, "Dimension needs to be greater than zero");
	return *this->components;
}

template <typename Type, UNSIGNED_TYPE Dimension>
Type & ms::math::Vector<Type, Dimension>::x () {
	static_assert(Dimension > 0, "Dimension needs to be greater than zero");
	return *this->components;
}

template <typename Type, UNSIGNED_TYPE Dimension>
Type const & ms::math::Vector<Type, Dimension>::y () const {
	static_assert(Dimension > 1, "Dimension needs to be greater than one");
	return *(this->components + 1);
}

template <typename Type, UNSIGNED_TYPE Dimension>
Type & ms::math::Vector<Type, Dimension>::y () {
	static_assert(Dimension > 1, "Dimension needs to be greater than one");
	return *(this->components + 1);
}

template <typename Type, UNSIGNED_TYPE Dimension>
Type const & ms::math::Vector<Type, Dimension>::z () const  {
	static_assert(Dimension > 2, "Dimension needs to be greater than two");
	return *(this->components + 2);
}

template <typename Type, UNSIGNED_TYPE Dimension>
Type & ms::math::Vector<Type, Dimension>::z ()  {
	static_assert(Dimension > 2, "Dimension needs to be greater than two");
	return *(this->components + 2);
}

template <typename Type, UNSIGNED_TYPE Dimension>
Type const & ms::math::Vector<Type, Dimension>::w () const  {
	static_assert(Dimension > 3, "Dimension needs to be greater than three");
	return *(this->components + 3);
}

template <typename Type, UNSIGNED_TYPE Dimension>
Type & ms::math::Vector<Type, Dimension>::w () {
	static_assert(Dimension > 3, "Dimension needs to be greater than three");
	return *(this->components + 3);
}

#endif /* vector_h */
