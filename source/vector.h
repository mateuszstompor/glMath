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
#include <cmath>
#include <cstring>

namespace ms {
    
	namespace math {
		
		template <typename Type, std::uint16_t Dimension>
		class Vector {
		
		public:
			
							Vector				();
							Vector				(Type value);
							Vector				(Vector && v);
							Vector				(const Vector & v);
							Vector				(const Type array [Dimension]);
			
							~Vector();
			
			Vector &		operator	=		(const Vector & v);
			Vector &		operator	=		(Vector && v);
			bool			operator	==		(const Vector & v) const;
			bool			operator	!=		(const Vector & v) const;
			Vector			operator	+		(const Vector & v) const;
			Vector & 		operator 	+= 		(const Vector & v);
			Vector 			operator 	- 		(const Vector & v) const;
			Vector & 		operator 	-= 		(const Vector & v);
			Vector 			operator 	* 		(float value) const;
			Vector& 		operator 	*= 		(float value);
			
			Type & 			operator 	[] 		(std::uint16_t position);
			Type & 			at					(std::uint16_t position);
			float 			dot					(const Vector & v) const;
			Vector 			cross				(const Vector & v) const;
			
			float	 		length				() const;
			
			void	 		normalize			();
			
			std::string 	to_string			() const;
			
			const Type * 	c_array				() const;
			
		private:
			
			Type * 			components;
			
		};
		
	}
    
}

template <typename Type, std::uint16_t Dimension>
ms::math::Vector<Type, Dimension>::Vector() : components( new Type[Dimension] ) { }

template <typename Type, std::uint16_t Dimension>
ms::math::Vector<Type, Dimension>::Vector(Type value) : Vector() {
    
    for (std::uint16_t i = 0; i < Dimension; ++i)
        components[i] = value;
    
}

template <typename Type, std::uint16_t Dimension>
ms::math::Vector<Type, Dimension>::Vector(Vector && v) : components(v.components) {
    v.components = nullptr;
}

template <typename Type, std::uint16_t Dimension>
ms::math::Vector<Type, Dimension>::Vector(const Vector & v) : components( new Type[Dimension] ) {
    memcpy((*this).components, v.components, Dimension * sizeof(Type));
}

template <typename Type, std::uint16_t Dimension>
ms::math::Vector<Type, Dimension>::Vector(const Type array [Dimension]) : components( new Type[Dimension] ) {
	memcpy((*this).components, array, Dimension * sizeof(Type));
}

template <typename Type, std::uint16_t Dimension>
ms::math::Vector<Type, Dimension>& ms::math::Vector<Type, Dimension>::operator=(const Vector & v) {
    memcpy((*this).components, v.components, Dimension * sizeof(Type));
    return *this;
}

template <typename Type, std::uint16_t Dimension>
ms::math::Vector<Type, Dimension>& ms::math::Vector<Type, Dimension>::operator=(Vector && v) {
    delete [] (*this).components;
    
    (*this).components = v.components;
    v.components = nullptr;
    
    return *this;
}

template <typename Type, std::uint16_t Dimension>
ms::math::Vector<Type, Dimension>::~Vector() {
    delete [] this->components;
}

template <typename Type, std::uint16_t Dimension>
bool ms::math::Vector<Type, Dimension>::operator == (const Vector & v) const {
    for(std::uint16_t i = 0; i < Dimension; ++i)
        if (v.components[i] != (*this).components[i])
            return false;
    return true;
}

template <typename Type, std::uint16_t Dimension>
bool ms::math::Vector<Type, Dimension>::operator != (const Vector & v) const {
    return !( *this == v );
}

template <typename Type, std::uint16_t Dimension>
float ms::math::Vector<Type, Dimension>::dot(const Vector & v) const {
    float dotProduct = 0.0f;
    
    for(std::uint16_t i = 0; i < Dimension; ++i)
        dotProduct += (*this).components[i] * v.components[i];
    
    return dotProduct;
}

template <typename Type, std::uint16_t Dimension>
ms::math::Vector<Type, Dimension> ms::math::Vector<Type, Dimension>::cross(const Vector & v) const {
	static_assert(Dimension == 3, "Cross product exists only for dimension of three");
	Vector vec;
	vec[0] = this->components[1] * v.components[2] - this->components[2] * v.components[1];
	vec[1] = this->components[2] * v.components[0] - this->components[0] * v.components[2];
	vec[2] = this->components[0] * v.components[1] - this->components[1] * v.components[0];
	return vec;
}

template <typename Type, std::uint16_t Dimension>
ms::math::Vector<Type, Dimension> & ms::math::Vector<Type, Dimension>::operator *= (float value) {
    
    for(std::uint16_t i = 0; i < Dimension; ++i)
        (*this).components[i] *= value;
    
    return *this;
    
}

template <typename Type, std::uint16_t Dimension>
ms::math::Vector<Type, Dimension> ms::math::Vector<Type, Dimension>::operator * (float value) const {
    
    Vector vec;
    
    for(std::uint16_t i = 0; i < Dimension; ++i)
        vec.components[i] = (*this).components[i] * value;
    
    return vec;
    
}

template <typename Type, std::uint16_t Dimension>
Type& ms::math::Vector<Type, Dimension>::at(std::uint16_t position) {
    return (*this).components[position];
}

template <typename Type, std::uint16_t Dimension>
Type& ms::math::Vector<Type, Dimension>::operator [] (std::uint16_t position) {
    return (*this).components[position];
}

template <typename Type, std::uint16_t Dimension>
ms::math::Vector<Type, Dimension> operator * (float value, const ms::math::Vector<Type, Dimension> & v) {
    ms::math::Vector<Type, Dimension> vec(v);
    return vec * value;
}

template <typename Type, std::uint16_t Dimension>
ms::math::Vector<Type, Dimension> ms::math::Vector<Type, Dimension>::operator + (const Vector & v) const {
    Vector vec;
    
    for(std::uint16_t i = 0; i < Dimension; ++i)
        vec.components[i] = (*this).components[i] + v.components[i];
    
    return vec;
}

template <typename Type, std::uint16_t Dimension>
ms::math::Vector<Type, Dimension> ms::math::Vector<Type, Dimension>::operator - (const Vector & v) const {
    Vector vec;
    
    for(std::uint16_t i = 0; i < Dimension; ++i)
        vec.components[i] = (*this).components[i] - v.components[i];
    
    return vec;
}

template <typename Type, std::uint16_t Dimension>
ms::math::Vector<Type, Dimension> & ms::math::Vector<Type, Dimension>::operator += (const Vector & v) {
    
    for(std::uint16_t i = 0; i < Dimension; ++i)
        (*this).components[i] += v.components[i];
    
    return *this;
    
}

template <typename Type, std::uint16_t Dimension>
ms::math::Vector<Type, Dimension> & ms::math::Vector<Type, Dimension>::operator -= (const Vector & v) {
    
    for(std::uint16_t i = 0; i < Dimension; ++i)
        (*this).components[i] -= v.components[i];
    
    return *this;
    
}

template <typename Type, std::uint16_t Dimension>
float ms::math::Vector<Type, Dimension>::length() const {
    float length = 0.0;
    
    for(std::uint16_t i = 0; i < Dimension; ++i)
        length += (*this).components[i] * (*this).components[i];
    
    return std::sqrt(length);
}

template <typename Type, std::uint16_t Dimension>
void ms::math::Vector<Type, Dimension>::normalize() {
	float len = length();
	for(std::uint16_t i = 0; i < Dimension; ++i)
		components[i] /= len;
}

template <typename Type, std::uint16_t Dimension>
std::string ms::math::Vector<Type, Dimension>::to_string() const {
    std::ostringstream output;
    
    for (std::uint16_t i = 0; i < Dimension; ++i)
        output << components[i] << " ";
    
    return output.str();
}

template <typename Type, std::uint16_t Dimension>
const Type * ms::math::Vector<Type, Dimension>::c_array() const {
    return components;
}

#endif /* vector_h */
