//
//  common.h
//  glMath
//
//  Created by Mateusz Stompór on 22/02/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#pragma once

#include <cstdint>
#include <cassert>
#include <iostream>

#ifdef __WIN32__

    #define _USE_MATH_DEFINES
    #include <math.h>

#else

    #include <cmath>

#endif


namespace ms {

	namespace math {

		#define UNSIGNED_TYPE std::uint8_t

	}

}

// FUNCTIONS

namespace ms {
	
	template <typename Type>
	inline bool equal(Type value, Type actualValue, Type precision) {
		
		if(actualValue < (value - precision) || actualValue > (value + precision)) {
			return false;
		}
		
		return true;
	}
	
	template <typename Type>
	inline void assert_equal(Type value, Type actualValue, Type precision) {
		if(!equal(value, actualValue, precision)) {
			std::cerr << value << " is not equal " << actualValue << '\n';
			assert(false);
		}
	}
	
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

		// sqrt
		template <typename Type>
		inline Type square_root(Type number) {
			return sqrt(static_cast<double>(number));
		}
		
		template <>
		inline float square_root(float number) {
			return sqrt(number);
		}
		
		namespace point {
			
			template <typename Type>
			inline Type middle(Type p0, Type p1) {
				return (p0 + p1)/Type(2);
			}
			
			template <typename Type>
			inline Type distance(Type p0, Type p1) {
				return abs(p0 - p1);
			}
			
		}

	}

}
