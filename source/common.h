//
//  common.h
//  glMath
//
//  Created by Mateusz Stompór on 22/02/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#ifndef common_h
#define common_h

#include <cstdint>
#include <cmath>

// CONSTANS

namespace ms {
	
	namespace math {
		
		#define UNSIGNED_TYPE std::uint8_t
	
	}

}

// FUNCTIONS

namespace ms {
	
	namespace math {
		
		// function that converts radians to angle in degrees
		template <typename Type>
		inline Type degrees(Type radians) {
			return radians * 180.0f / M_PI;
		}
		
		template <>
		inline double degrees(double radians) {
			return radians * 180.0 / M_PI;
		}
		
		template <typename Type>
		inline Type radians(Type degrees) {
			return M_PI * (degrees / 180.0f);
		}
		
		template <>
		inline double radians(double degrees) {
			return M_PI * (degrees / 180.0);
		}
		
		
		// cosine
		template <typename Type>
		inline Type cosine(Type radians) {
			return cos(radians);
		}
		
		template <>
		inline float cosine(float radians) {
			return cosf(radians);
		}
		
		// sinus
		template <typename Type>
		inline Type sinus(Type radians) {
			return sin(radians);
		}
		
		template <>
		inline float sinus(float radians) {
			return sinf(radians);
		}
		
		
	}
	
}


#endif /* common_h */
