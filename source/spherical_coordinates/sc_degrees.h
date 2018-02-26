//
//  sc_degrees.h
//  glMath
//
//  Created by Mateusz Stompór on 24/02/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#ifndef sc_degrees_h
#define sc_degrees_h

#include "../common.h"

#include <cmath>

namespace ms {
	
	namespace math {
	
		template <typename T, UNSIGNED_TYPE Dimension>
		class Vector;
		
		//spherical coordinates
		namespace spco {
			
			template <typename Type>
			struct RadiansSpherical;
			
			template <typename Type>
			struct DegreesSpherical {
				
			public:
				
				DegreesSpherical(Type inclination, Type azimuthAngle, Type radius);
				DegreesSpherical(ms::math::Vector<Type, 3> v);
				DegreesSpherical(RadiansSpherical<Type> radiansSpherical);
				DegreesSpherical();
				
				// measured from azimuth
				Type 				inclination;
				// measure of the angle (looking from northern direction)
				Type 				azimuthAngle;
				Type 				radius;
				
			};
			
		}
		
	}

}

template <typename Type>
ms::math::spco::DegreesSpherical<Type>::DegreesSpherical(Type inclination, Type azimuthAngle, Type radius)
: inclination(inclination), azimuthAngle(azimuthAngle), radius(radius) { }

template <typename Type>
ms::math::spco::DegreesSpherical<Type>::DegreesSpherical(RadiansSpherical<Type> radiansSpherical)
: DegreesSpherical(ms::math::degrees<Type>(radiansSpherical.inclination), ms::math::degrees<Type>(radiansSpherical.azimuthAngle), radiansSpherical.radius) { }

template <typename Type>
ms::math::spco::DegreesSpherical<Type>::DegreesSpherical(ms::math::Vector<Type, 3> v) {
	radius 			= sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	azimuthAngle 	= v[0] 		== 0 ? 0 : ms::math::degrees(std::atan(v[1] / v[0]));
	inclination 	= radius 	== 0 ? 0 : ms::math::degrees(std::acos(v[2] / radius));
}

template <typename Type>
ms::math::spco::DegreesSpherical<Type>::DegreesSpherical() : DegreesSpherical(0, 0, 0) { }

#endif
