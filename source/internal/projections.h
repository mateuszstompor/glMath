//
//  projections.h
//  glMath
//
//  Created by Mateusz Stompór on 27/02/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#ifndef projections_h
#define projections_h

namespace ms {
	
	namespace math {
		
		template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
		class Matrix;
		
		namespace projection {
			
			template <typename Type>
			Matrix<Type, 4, 4> perspective(Type nearPlane, Type farPlane, Type fovDegrees, Type aspectRatio) {
				
				Matrix<Type, 4, 4> p;
				
				Type q = Type(1.0) / ms::math::radians<Type>(Type(0.5) * fovDegrees);
				Type A = q / aspectRatio;
				Type B = (nearPlane + farPlane) / (nearPlane - farPlane);
				Type C = (Type(2.0) * nearPlane * farPlane) / (nearPlane - farPlane);
				
				// First column
				p[0] 	= A;
				p[1] 	= Type(0.0);
				p[2] 	= Type(0.0);
				p[3] 	= Type(0.0);
				
				// Second column
				p[4] 	= Type(0.0);
				p[5] 	= q;
				p[6] 	= Type(0.0);
				p[7]	= Type(0.0);
				
				// Third column
				p[8] 	= Type(0.0);
				p[9] 	= Type(0.0);
				p[10]	= B;
				p[11] 	= Type(-1.0);
				
				// Fourth column
				p[12] 	= Type(0.0);
				p[13] 	= Type(0.0);
				p[14]	= C;
				p[15] 	= Type(0.0);
				
				return p;
			}
			
			template <typename Type>
			Matrix<Type, 4, 4> orthogonal(Type _far, Type _near,
										  Type _top, Type _bottom,
										  Type _left, Type _right) {
				
				Matrix<Type, 4, 4> p;
				
				// First column
				p[0] 	= Type(2.0)/(_right - _left);
				p[1] 	= Type(0.0);
				p[2] 	= Type(0.0);
				p[3] 	= Type(0.0);
				
				// Second column
				p[4] 	= Type(0.0);
				p[5] 	= Type(2.0)/(_top - _bottom);
				p[6] 	= Type(0.0);
				p[7]	= Type(0.0);
				
				// Third column
				p[8] 	= Type(0.0);
				p[9] 	= Type(0.0);
				p[10]	= -Type(2.0)/(_far - _near);
				p[11] 	= Type(0.0);
				
				// Fourth column
				p[12] 	= -((_right + _left)/(_right - _left));
				p[13] 	= -((_top + _bottom)/(_top - _bottom));
				p[14]	= -((_far + _near)/(_far - _near));
				p[15] 	= Type(1.0);
				
				return p;
			}
			
		}
		
	}
	
}

#endif /* projections_h */
