//
//  sc_radians.h
//  glMath
//
//  Created by Mateusz Stompór on 25/02/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#ifndef sc_radians_h
#define sc_radians_h

#include "../common.h"

#include <cmath>

namespace ms {
	
	namespace math {
	
		template <typename T, UNSIGNED_TYPE Dimension>
		class Vector;
		
		//spherical coordinates
		namespace spco {
			
			template <typename Type>
			struct DegreesSpherical;
			
			template <typename Type>
			struct RadiansSpherical {
				
			public:
				
				RadiansSpherical(Type inclination, Type azimuthAngle, Type radius);
				RadiansSpherical(ms::math::Vector<Type, 3> v);
				RadiansSpherical(DegreesSpherical<Type> degreesSpherical);
				RadiansSpherical();
				
				Type 				inclination;
				Type 				azimuthAngle;
				Type 				radius;
				
			};
			
		}
		
	}

}

template <typename Type>
ms::math::spco::RadiansSpherical<Type>::RadiansSpherical(Type inclination, Type azimuthAngle, Type radius)
: inclination(inclination), azimuthAngle(azimuthAngle), radius(radius) { }

template <typename Type>
ms::math::spco::RadiansSpherical<Type>::RadiansSpherical(DegreesSpherical<Type> radiansSpherical)
: RadiansSpherical(ms::math::radiansf(radiansSpherical.inclination), ms::math::radiansf(radiansSpherical.azimuthAngle), radiansSpherical.radius) { }

template <typename Type>
ms::math::spco::RadiansSpherical<Type>::RadiansSpherical(ms::math::Vector<Type, 3> v) {
	radius 			= sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	azimuthAngle 	= v[0] 		== 0 ? 0 : std::atan(v[1] / v[0]);
	inclination 	= radius 	== 0 ? 0 : std::acos(v[2] / radius);
}

template <typename Type>
ms::math::spco::RadiansSpherical<Type>::RadiansSpherical() : RadiansSpherical(0, 0, 0) { }

#endif
