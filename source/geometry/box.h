//
//  box.h
//  glMath
//
//  Created by Mateusz Stompór on 17/04/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#pragma once

//
//               e-------f
//              /|      /|
//             / |     / |
//            a--|----b  |
//            |  g----|--h
//            | /     | /
//            c-------d
//
//                 ^
//                 |       direction of sight
//               camera
//
//
// points {c, d, g, h} - plane bottom
// points {a, b, e, f} - plane top
// points {c, g, a, e} - plane left
// points {d, b, h, f} - plane right
// points {a, b, c, d} - plane front
// points {g, e, f, h} - plane back

namespace ms {
	
	namespace math {
	
		enum class BoxPlane {
			front, back,
			left, right,
			top, bottom
		};
		
		template <typename Type>
		struct BoxCorners {
			
			using vec3T = Vector<Type, 3>;
			
			//corners
			vec3T a, b, c, d, e, f, g, h;
			
		};
		
		template <typename Type>
		struct BoxPlanes {
			
			using vec3T = Vector<Type, 3>;
			
			Plane<Type>     front;
			Plane<Type>     back;
			
			Plane<Type>     top;
			Plane<Type>     bottom;
			
			Plane<Type>     left;
			Plane<Type>     right;
			
		};
		
	}
	
}
