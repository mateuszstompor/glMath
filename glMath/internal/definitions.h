//
//  definitions.h
//  glMath
//
//  Created by Mateusz Stompór on 22/02/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#pragma once

#include "common.h"
#include "../geometry/plane.h"
#include "../geometry/triangle.h"

namespace ms::math {
    template <typename T, std::uint8_t Dimension>
    class Vector;
    template <typename Type, std::uint8_t Rows, std::uint8_t Columns>
    class Matrix;
    template <typename Type>
    class FrustumViewport;
}

namespace ms::math {
    // Matrices
    typedef ms::math::Matrix<float, 2, 2>       mat2;
    typedef ms::math::Matrix<float, 3, 3>       mat3;
    typedef ms::math::Matrix<float, 4, 4>       mat4;
    typedef ms::math::Matrix<double, 2, 2>      mat2d;
    typedef ms::math::Matrix<double, 3, 3>      mat3d;
    typedef ms::math::Matrix<double, 4, 4>      mat4d;
    // Vectors
    typedef ms::math::Vector<float, 2>          vec2;
    typedef ms::math::Vector<float, 3>          vec3;
    typedef ms::math::Vector<float, 4>          vec4;
    typedef ms::math::Vector<double, 2>         vec2d;
    typedef ms::math::Vector<double, 3>         vec3d;
    typedef ms::math::Vector<double, 4>         vec4d;
    typedef ms::math::FrustumViewport<float>    frustum4f;
    // Ray
    typedef ms::math::Ray<float, 3>             ray3f;
    typedef ms::math::Ray<float, 4>             ray4f;
    // Plane
    typedef ms::math::Plane<float>              planef;
    typedef ms::math::Plane<double>             planed;
    // Triangle
    typedef ms::math::Triangle<float, 3>        triangle3f;
    typedef ms::math::Triangle<double, 3>       triangle3d;
}
