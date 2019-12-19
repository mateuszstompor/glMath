//
//  ray_tests.hpp
//  glMath
//
//  Created by Mateusz Stompór on 19/12/2019.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#pragma once

#include <gtest/gtest.h>
#include <glMath/glMath.h>

using namespace ms::math;

class RayTestFixture: public ::testing::Test {
};

TEST_F(RayTestFixture, OriginInitialization) {
    Ray<float, 3> ray(vec3(1, 2, 3), vec3(1, 0, 0));
    vec3 expected_origin {1, 2, 3};
    ASSERT_EQ(expected_origin, ray.origin);
}

TEST_F(RayTestFixture, DirectionInitialization) {
    Ray<float, 3> ray(vec3(1, 2, 3), vec3(1, 0, 0));
    vec3 expected_direction {1, 0, 0};
    ASSERT_EQ(expected_direction, ray.direction);
}
