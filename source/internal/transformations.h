//
//  transformations.h
//  glMath
//
//  Created by Mateusz Stompór on 25/02/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#ifndef transformations_h
#define transformations_h

namespace ms {
	
	namespace math {
		
		template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
		class Matrix;
		
		namespace transform {
			
			template <typename Type, UNSIGNED_TYPE Dimension>
			Matrix<Type, Dimension, Dimension> scale (std::initializer_list<Type> scaleFactors) {
				static_assert(	Dimension	>=	2		, "Matrix needs to at least two - dimensional" );
				
				Matrix<Type, Dimension, Dimension> scale = Matrix<Type, Dimension, Dimension>::identity();
				
				for (UNSIGNED_TYPE i = 0; i < scaleFactors.size(); ++i) {
					scale[i * Dimension + i] = *(scaleFactors.begin() + i);
				}
				
				return scale;
			}
			
			template <typename Type, UNSIGNED_TYPE Dimension>
			Matrix<Type, Dimension, Dimension> translate (std::initializer_list<Type> translationFactors) {
				static_assert(	Dimension	>=	2		, "Matrix needs to at least two - dimensional" );
				
				Matrix<Type, Dimension, Dimension> translation = Matrix<Type, Dimension, Dimension>::identity();
				
				for (UNSIGNED_TYPE i = 0; i < translationFactors.size(); ++i) {
					translation[(Dimension - 1) * Dimension + i] = *(translationFactors.begin() + i);
				}
				
				return translation;
			}
			
			template <typename Type, UNSIGNED_TYPE Dimension>
			Matrix<Type, Dimension, Dimension> rotateAboutXRadians (Type radians) {
				Matrix<Type, Dimension, Dimension> rotation = Matrix<Type, Dimension, Dimension>::identity();
				static_assert(	Dimension	==	3	||	Dimension	==	4, "Matrix needs to at three or four - dimensional" );
				
				rotation[Dimension + 1] = 		cosine<Type>(radians);
				rotation[Dimension + 2] = 		sinus<Type>(radians);
				
				rotation[2 * Dimension + 1] = 	-sinus<Type>(radians);
				rotation[2 * Dimension + 2] = 	cosine<Type>(radians);
				
				return rotation;
			}
			
			template <typename Type, UNSIGNED_TYPE Dimension>
			Matrix<Type, Dimension, Dimension> rotateAboutYRadians (Type radians) {
				Matrix<Type, Dimension, Dimension> rotation = Matrix<Type, Dimension, Dimension>::identity();
		
				static_assert(	Dimension	==	3	||	Dimension	==	4, "Matrix needs to at three or four - dimensional" );
				
				rotation[0] = 					cosine<Type>(radians);
				rotation[2] = 					-sinus<Type>(radians);
				
				rotation[2 * Dimension] = 		sinus<Type>(radians);
				rotation[2 * Dimension + 2] = 	cosine<Type>(radians);
				
				return rotation;
			}
			
			template <typename Type, UNSIGNED_TYPE Dimension>
			Matrix<Type, Dimension, Dimension> rotateAboutZRadians (Type radians) {
				Matrix<Type, Dimension, Dimension> rotation = Matrix<Type, Dimension, Dimension>::identity();
				
				static_assert(	Dimension	==	3	||	Dimension	==	4, "Matrix needs to at three or four - dimensional" );
				
				rotation[0] = 				cosine<Type>(radians);
				rotation[1] = 				sinus<Type>(radians);
				
				rotation[Dimension] = 		-sinus<Type>(radians);
				rotation[Dimension + 1] = 	cosine<Type>(radians);
				
				return rotation;
			}
			
			// VECTOR NEEDS TO BE NORMALIZED
			template <typename Type, UNSIGNED_TYPE Dimension>
			Matrix<Type, Dimension, Dimension> rotateAboutAxis (Type radians, Vector<Type, Dimension> v) {
				Matrix<Type, Dimension, Dimension> rotation = Matrix<Type, Dimension, Dimension>::identity();
				static_assert(	Dimension	==	3	||	Dimension	==	4, "Matrix needs to at three or four - dimensional" );
				
				// First column
				rotation[0] = cosine<Type>(radians) + v[0]*v[0]*(1 - cosine<Type>(radians));
				rotation[1] = v[0]*v[1]*(1 - cosine<Type>(radians)) + v[2] * sinus<Type>(radians);
				rotation[2] = v[2]*v[1]*(1 - cosine<Type>(radians)) - v[1] * sinus<Type>(radians);
				
				// Second column
				rotation[Dimension] = v[0]*v[1]*(1 - cosine<Type>(radians)) - v[2] * sinus<Type>(radians);
				rotation[Dimension + 1] = cosine<Type>(radians) + v[1]*v[1]*(1 - cosine<Type>(radians));
				rotation[Dimension + 2] = v[2]*v[1]*(1 - cosine<Type>(radians)) + v[0] * sinus<Type>(radians);
				
				// Third column
				rotation[2 * Dimension] = v[0]*v[2]*(1 - cosine<Type>(radians)) + v[1] * sinus<Type>(radians);
				rotation[2 * Dimension + 1] = v[1]*v[2]*(1 - cosine<Type>(radians)) - v[0] * sinus<Type>(radians);
				rotation[2 * Dimension + 2] = cosine<Type>(radians) + v[2]*v[2]*(1 - cosine<Type>(radians));
				
				return rotation;
			}
			
		}
		
	}
	
}

#endif /* transformations_h */
