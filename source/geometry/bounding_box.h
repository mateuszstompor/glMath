//
//  boundingBox.h
//  ngin
//
//  Created by Mateusz Stompór on 31/03/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#ifndef boundingBox_hpp
#define boundingBox_hpp

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
			
		public:
			
							BoundingBox		(Type x, Type X,
											 Type y, Type Y,
											 Type z, Type Z);
			
			Type 			get_width_x		() const;
			Type 			get_height_y	() const;
			Type 			get_depth_z		() const;
			vec3T const & 	get_origin		() const;
			
		protected:
			
			Type width_x, height_y, depth_z;
			
			Type minX, maxX;
			Type minY, maxY;
			Type minZ, maxZ;
			
			vec3T origin;
			
			//corners
			vec3T xyz;
			vec3T xyZ;
			vec3T xYz;
			vec3T xYZ;
			
			vec3T Xyz;
			vec3T XyZ;
			vec3T XYz;
			vec3T XYZ;
			
		};
		
	}
    
}

template <typename Type>
ms::math::BoundingBox<Type>::BoundingBox(Type x, Type X, Type y, Type Y, Type z, Type Z) : minX(x), maxX(X), minY(y), maxY(Y), minZ(z), maxZ(Z) {
	
	xyz = vec3T{x, y, z};
	xyZ = vec3T{x, y, Z};
	xYz = vec3T{x, Y, z};
	xYZ = vec3T{x, Y, Z};
	
	Xyz = vec3T{X, y, z};
	XyZ = vec3T{X, y, Z};
	XYz = vec3T{X, Y, z};
	XYZ = vec3T{X, Y, Z};
	
	origin = vec3T{math::point::middle(x, X), math::point::middle(y, Y), math::point::middle(z, Z)};
	
	width_x = math::point::distance(x, X);
	height_y = math::point::distance(y, Y);
	depth_z = math::point::distance(z, Z);
	
}

template <typename Type>
Type ms::math::BoundingBox<Type>::get_width_x () const {
	return width_x;
}

template <typename Type>
Type ms::math::BoundingBox<Type>::get_height_y () const {
	return height_y;
}

template <typename Type>
Type ms::math::BoundingBox<Type>::get_depth_z () const {
	return depth_z;
}

template <typename Type>
ms::math::Vector<Type, 3> const & ms::math::BoundingBox<Type>::get_origin () const {
	return origin;
}

#endif /* boundingBox_h */
