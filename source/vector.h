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

namespace ms {
    
    namespace math {
        
        template <typename Type, std::uint16_t Dimension>
        class Vector {
        
        public:
            
            //constructors
            //create and do not initialize memory
            Vector();
            //create and initialize memory with value
            Vector(Type value);
            //move constructor
            Vector(Vector && v);
            //copy constructor
            Vector(const Vector & v);
            
            virtual Vector& operator=(const Vector & v);
            virtual Vector& operator=(Vector && v);

            virtual ~Vector();
            
            bool operator == (const Vector & v) const;
            bool operator != (const Vector & v) const;
            
            
            std::string to_string() const;
            
            const Type * c_array() const;
            
        protected:
            
            Type* components;
            
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
