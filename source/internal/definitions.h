//
//  definitions.h
//  glMath
//
//  Created by Mateusz Stompór on 22/02/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#include "common.h"

#pragma once

namespace ms {
	
	namespace math {
		
		template <typename T, UNSIGNED_TYPE Dimension>
		class Vector;

		template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
		class Matrix;

		template <typename Type>
		class FrustumViewport;

	}
	
}

namespace ms {
	
	namespace math {
		
		//matrices
		
		typedef ms::math::Matrix<float, 2, 2> mat2;
		typedef ms::math::Matrix<float, 3, 3> mat3;
		typedef ms::math::Matrix<float, 4, 4> mat4;
		
		typedef ms::math::Matrix<double, 2, 2> mat2d;
		typedef ms::math::Matrix<double, 3, 3> mat3d;
		typedef ms::math::Matrix<double, 4, 4> mat4d;
		
		//vectors
		typedef ms::math::Vector<float, 2> vec2;
		typedef ms::math::Vector<float, 3> vec3;
		typedef ms::math::Vector<float, 4> vec4;
		
		typedef ms::math::Vector<double, 2> vec2d;
		typedef ms::math::Vector<double, 3> vec3d;
		typedef ms::math::Vector<double, 4> vec4d;
		typedef ms::math::FrustumViewport<float> frustum4f;
		
	}
	
}