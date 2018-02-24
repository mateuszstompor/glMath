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
		
		inline double degrees(double radians) {
			return radians * 180.0 / M_PI;
		}
		
		inline float degreesf(float radiansf) {
			return radiansf * 180.0f / M_PI;
		}
		
	}
	
}


#endif /* common_h */
