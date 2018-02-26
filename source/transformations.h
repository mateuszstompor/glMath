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
			
			template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
			Matrix<Type, Rows, Columns> scale (std::initializer_list<Type> scaleFactors) {
				static_assert(	Rows 	== 	Columns	, "Matrix needs to be square" );
				static_assert(	Rows	>=	2		, "Matrix needs to at least two - dimensional" );
				
				Matrix<Type, Rows, Columns> scale = Matrix<Type, Rows, Columns>::identity();
				
				for (UNSIGNED_TYPE i = 0; i < scaleFactors.size(); ++i) {
					scale[i * Rows + i] = *(scaleFactors.begin() + i);
				}
				
				return scale;
			}
			
			template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
			Matrix<Type, Rows, Columns> translate (std::initializer_list<Type> translationFactors) {
				static_assert(	Rows 	== 	Columns	, "Matrix needs to be square" );
				static_assert(	Rows	>=	2		, "Matrix needs to at least two - dimensional" );
				
				Matrix<Type, Rows, Columns> translation = Matrix<Type, Rows, Columns>::identity();
				
				for (UNSIGNED_TYPE i = 0; i < translationFactors.size(); ++i) {
					translation[(Rows - 1) * Rows + i] = *(translationFactors.begin() + i);
				}
				
				return translation;
			}
			
			template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
			Matrix<Type, Rows, Columns> rotateAboutXRadians (Type radians) {
				Matrix<Type, Rows, Columns> rotation = Matrix<Type, Rows, Columns>::identity();
				static_assert(	Rows 	== 	Columns	, "Matrix needs to be square" );
				static_assert(	Rows	==	3	||	Rows	==	4, "Matrix needs to at three or four - dimensional" );
				
				rotation[Rows + 1] = 		cosf(radians);
				rotation[Rows + 2] = 		sinf(radians);
				
				rotation[2 * Rows + 1] = 	-sinf(radians);
				rotation[2 * Rows + 2] = 	cosf(radians);
				
				return rotation;
			}
			
			template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
			Matrix<Type, Rows, Columns> rotateAboutYRadians (Type radians) {
				Matrix<Type, Rows, Columns> rotation = Matrix<Type, Rows, Columns>::identity();
				static_assert(	Rows 	== 	Columns	, "Matrix needs to be square" );
				static_assert(	Rows	==	3	||	Rows	==	4, "Matrix needs to at three or four - dimensional" );
				
				rotation[0] = 				cosf(radians);
				rotation[2] = 				-sinf(radians);
				
				rotation[2 * Rows] = 		sinf(radians);
				rotation[2 * Rows + 2] = 	cosf(radians);
				
				return rotation;
			}
			
			template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
			Matrix<Type, Rows, Columns> rotateAboutZRadians (Type radians) {
				Matrix<Type, Rows, Columns> rotation = Matrix<Type, Rows, Columns>::identity();
				static_assert(	Rows 	== 	Columns	, "Matrix needs to be square" );
				static_assert(	Rows	==	3	||	Rows	==	4, "Matrix needs to at three or four - dimensional" );
				
				rotation[0] = 			cosf(radians);
				rotation[1] = 			sinf(radians);
				
				rotation[Rows] = 		-sinf(radians);
				rotation[Rows + 1] = 	cosf(radians);
				
				return rotation;
			}
			
		}
		
	}
	
}

#endif /* transformations_h */
