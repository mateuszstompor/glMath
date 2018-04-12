//
//  boundingBox.h
//  ngin
//
//  Created by Mateusz Stompór on 31/03/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#ifndef boundingBox_hpp
#define boundingBox_hpp

#include <cassert>
#include <vector>
#include <iostream>

#include "../internal/definitions.h"
#include "../internal/common.h"

//
//               e-------f
//              /|      /|
//             / |     / |
//            a--|----b  |
//            |  g----|--h
//            | /     | /
//            c-------d
//

namespace ms {
    
	namespace math {
		
		template <typename Type>
		class Plane;
		
		template <typename Type>
		class BoundingBox {
			
			friend class Plane<Type>;
			
		protected:
			
			typedef Vector<Type, 3> vec3T;
			typedef Vector<Type, 4> vec4T;
			
		public:
			
										BoundingBox		(Type x, Type X,
														 Type y, Type Y,
														 Type z, Type Z);
			
			constexpr vec4T &			operator []		(size_t index);
			constexpr vec4T const &		operator []		(size_t index) const;
			
			constexpr Type 				get_width_x		() const;
			constexpr Type 				get_height_y	() const;
			constexpr Type 				get_depth_z		() const;
			constexpr vec3T const & 	get_origin		() const;
			
		protected:
			
			Type width_x, height_y, depth_z;
			
			Type minX, maxX;
			Type minY, maxY;
			Type minZ, maxZ;
			
			vec3T origin;
			
			//corners
			std::vector<vec4T> corners{ };
			
		};
		
	}
    
}

template <typename Type>
ms::math::BoundingBox<Type>::BoundingBox(Type x, Type X, Type y, Type Y, Type z, Type Z) : minX(x), maxX(X), minY(y), maxY(Y), minZ(z), maxZ(Z) {
	
	corners.resize(8);
	
	corners[0] = vec4T{x, y, z, 1.0f};
	corners[1] = vec4T{x, y, Z, 1.0f};
	corners[2] = vec4T{x, Y, z, 1.0f};
	corners[3] = vec4T{x, Y, Z, 1.0f};
	
	corners[4] = vec4T{X, y, z, 1.0f};
	corners[5] = vec4T{X, y, Z, 1.0f};
	corners[6] = vec4T{X, Y, z, 1.0f};
	corners[7] = vec4T{X, Y, Z, 1.0f};
	
	origin = vec3T{math::point::middle(x, X), math::point::middle(y, Y), math::point::middle(z, Z)};
	
	width_x = math::point::distance(x, X);
	height_y = math::point::distance(y, Y);
	depth_z = math::point::distance(z, Z);
	
}

template <typename Type>
constexpr Type ms::math::BoundingBox<Type>::get_width_x () const {
	return width_x;
}

template <typename Type>
constexpr Type ms::math::BoundingBox<Type>::get_height_y () const {
	return height_y;
}

template <typename Type>
constexpr Type ms::math::BoundingBox<Type>::get_depth_z () const {
	return depth_z;
}

template <typename Type>
constexpr ms::math::Vector<Type, 3> const & ms::math::BoundingBox<Type>::get_origin () const {
	return origin;
}

template <typename Type>
constexpr typename ms::math::BoundingBox<Type>::vec4T & ms::math::BoundingBox<Type>::operator [] (size_t index) {
	return corners[index];
}

template <typename Type>
constexpr typename ms::math::BoundingBox<Type>::vec4T const & ms::math::BoundingBox<Type>::operator [] (size_t index) const {
	return corners[index];
}

#endif /* boundingBox_h */
