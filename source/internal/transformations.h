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
		
		template <typename T, UNSIGNED_TYPE Dimension>
		class Vector;
		
		namespace transform {
			
			template <typename Type, UNSIGNED_TYPE Dimension>
			Matrix<Type, Dimension, Dimension> scale (Vector<Type, (Dimension - 1) > scaleFactors) {
				static_assert(	Dimension	>=	2		, "Matrix needs to at least two - dimensional" );
				
				Matrix<Type, Dimension, Dimension> scale = Matrix<Type, Dimension, Dimension>::identity();
				
				for (UNSIGNED_TYPE i = 0; i < Dimension - 1; ++i) {
					scale[i * Dimension + i] = scaleFactors[i];
				}
				
				return scale;
			}
			
			template<typename Type>
			Matrix<Type, 4, 4> look_at (const Vector<Type, 3> & eyePosition, const Vector<Type, 3> & originPosition, const Vector<Type, 3> & upVector) {
				
				auto z = (originPosition - eyePosition).normalized();
				auto y = upVector.normalized();
				auto x = z.cross(y).normalized();
				
				Matrix<Type, 4, 4> m;
				
				m[0] = x[0];
				m[4] = x[1];
				m[8] = x[2];
				m[12] = -x.dot(eyePosition);

				m[1] = y[0];
				m[5] = y[1];
				m[9] = y[2];
				m[13] = -y.dot(eyePosition);

				m[2] = -z[0];
				m[6] = -z[1];
				m[10] = -z[2];
				m[14] = -z.dot(eyePosition);

				m[3] = Type(0.0);
				m[7] = Type(0.0);
				m[11] = Type(0.0);
				m[15] = Type(1.0);

				return m;
			}
			
			// TODO OPTIMIZE IT
			// Use when you do not need to have up vector specified precisely
			template<typename Type>
			Matrix<Type, 4, 4> directional_look (const Vector<Type, 3> & direction, const Vector<Type, 3> & eyePosition = Vector<Type, 3>(Type(0.0), Type(0.0), Type(0.0)))  {
				auto up = Vector<Type, 3>(direction[0], direction[1], direction[2] * Type(2.0)).cross(direction);
				return look_at(eyePosition, eyePosition + direction, up);
			}
			
			template <typename Type, UNSIGNED_TYPE Dimension>
			Matrix<Type, Dimension, Dimension> translate (Vector<Type, (Dimension - 1) > translationFactors) {
				static_assert(	Dimension	>=	2		, "Matrix needs to at least two - dimensional" );
				
				Matrix<Type, Dimension, Dimension> translation = Matrix<Type, Dimension, Dimension>::identity();
				
				for (UNSIGNED_TYPE i = 0; i < Dimension - 1; ++i) {
					translation[(Dimension - 1) * Dimension + i] = translationFactors[i];
				}
				
				return translation;
			}
			
			template <typename Type, UNSIGNED_TYPE Dimension>
			Matrix<Type, Dimension, Dimension> rotate_about_x_radians (Type radians) {
				Matrix<Type, Dimension, Dimension> rotation = Matrix<Type, Dimension, Dimension>::identity();
				static_assert(	Dimension	==	3	||	Dimension	==	4, "Matrix needs to at three or four - dimensional" );
				
				rotation[Dimension + 1] = 		cosine<Type>(radians);
				rotation[Dimension + 2] = 		sinus<Type>(radians);
				
				rotation[2 * Dimension + 1] = 	-sinus<Type>(radians);
				rotation[2 * Dimension + 2] = 	cosine<Type>(radians);
				
				return rotation;
			}
			
			template <typename Type, UNSIGNED_TYPE Dimension>
			Matrix<Type, Dimension, Dimension> rotate_about_y_radians (Type radians) {
				Matrix<Type, Dimension, Dimension> rotation = Matrix<Type, Dimension, Dimension>::identity();
		
				static_assert(	Dimension	==	3	||	Dimension	==	4, "Matrix needs to at three or four - dimensional" );
				
				rotation[0] = 					cosine<Type>(radians);
				rotation[2] = 					-sinus<Type>(radians);
				
				rotation[2 * Dimension] = 		sinus<Type>(radians);
				rotation[2 * Dimension + 2] = 	cosine<Type>(radians);
				
				return rotation;
			}
			
			template <typename Type, UNSIGNED_TYPE Dimension>
			Matrix<Type, Dimension, Dimension> rotate_about_z_radians (Type radians) {
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
			Matrix<Type, Dimension, Dimension> rotate_about_axis (Type radians, Vector<Type, Dimension> v) {
				Matrix<Type, Dimension, Dimension> rotation = Matrix<Type, Dimension, Dimension>::identity();
				static_assert(	Dimension	==	3	||	Dimension	==	4, "Matrix needs to at three or four - dimensional" );
				
				// First column
				rotation[0] = cosine<Type>(radians) + v[0]*v[0]*(1 - cosine<Type>(radians));
				rotation[1] = v[0]*v[1]*(1 - cosine<Type>(radians)) + v[2] * sinus<Type>(radians);
				rotation[2] = v[2]*v[1]*(1 - cosine<Type>(radians)) - v[1] * sinus<Type>(radians);
				
				// Second column
				rotation[Dimension] 	= v[0]*v[1]*(1 - cosine<Type>(radians)) - v[2] * sinus<Type>(radians);
				rotation[Dimension + 1] = cosine<Type>(radians) + v[1]*v[1]*(1 - cosine<Type>(radians));
				rotation[Dimension + 2] = v[2]*v[1]*(1 - cosine<Type>(radians)) + v[0] * sinus<Type>(radians);
				
				// Third column
				rotation[2 * Dimension] 	= v[0]*v[2]*(1 - cosine<Type>(radians)) + v[1] * sinus<Type>(radians);
				rotation[2 * Dimension + 1] = v[1]*v[2]*(1 - cosine<Type>(radians)) - v[0] * sinus<Type>(radians);
				rotation[2 * Dimension + 2] = cosine<Type>(radians) + v[2]*v[2]*(1 - cosine<Type>(radians));
				
				return rotation;
			}
			
		}
		
		template <typename Type>
		Vector<Type, 3> get_position (const Matrix<Type, 4, 4> & transformation) {
			return (transformation * Vector<Type, 4>(Type(0), Type(0), Type(0), Type(1))).xyz();
		}
		
		template <typename Type>
		Vector<Type, 3> up (const Matrix<Type, 4, 4> & transformation) {
			return Vector<Type, 3>{transformation[1], transformation[5], transformation[9]};
		}
		
		template <typename Type>
		Vector<Type, 3> right (const Matrix<Type, 4, 4> & transformation) {
			return Vector<Type, 3>{transformation[0], transformation[4], transformation[8]};
		}
		
		template <typename Type>
		Vector<Type, 3> back (const Matrix<Type, 4, 4> & transformation) {
			return Vector<Type, 3>{transformation[2], transformation[6], transformation[10]};
		}
		
	}
	
}

#endif /* transformations_h */
