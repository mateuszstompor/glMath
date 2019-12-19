//
//  plane_tests.hpp
//  glMath
//
//  Created by Mateusz Stompór on 19/12/2019.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#pragma once

#include <gtest/gtest.h>
#include <glMath/glMath.h>

using namespace ms::math;
using namespace ms::math::transform;

class PlaneTestFixture: public ::testing::Test {
};

TEST_F(PlaneTestFixture, IsInFront) {
    const BoundingBox<float> bb0 {0, 1, 0, 1, 0, 1};
    const BoundingBox<float> bb1 {-2, 1, -2, 1, -2, 1};
    const Plane<float> p0{vec3{0, 1, 0}, vec3{0, -1, 0}};
    ASSERT_TRUE(p0.is_in_front(bb0));
    ASSERT_FALSE(p0.is_in_front(bb1));
    const Plane<float> p1 = Plane<float>::from_points(vec3{4,2, 2}, vec3{2,2,2}, vec3{2,-1,2});
    const Plane<float> p2 {vec3{0,0,-1}, vec3{0,0,100}};
    ASSERT_TRUE(p2.is_in_front(bb0));
    ASSERT_TRUE(p1.is_in_front(bb0));
    ASSERT_TRUE(p1.get_position(bb0) == Plane<float>::RelativePosition::in_front);
}

TEST_F(PlaneTestFixture, RelativePosition) {
    BoundingBox<float> bb0 (0, 1, 0, 1, 0, 1);
    BoundingBox<float> bb1 (-2, 1, -2, 1, -2, 1);
    Plane<float> p0(vec3(0, 1, 0), vec3(0, -1, 0));
    Plane<float> p1(vec3(0, 1, 0), vec3(0, 2, 0));
    ASSERT_TRUE(p0.get_position(bb0) == ms::math::Plane<float>::RelativePosition::in_front);
    ASSERT_TRUE(p0.get_position(bb1) == ms::math::Plane<float>::RelativePosition::intersects);
    ASSERT_TRUE(p1.get_position(bb0) == ms::math::Plane<float>::RelativePosition::behind);
}

TEST_F(PlaneTestFixture, CreationFromThreePoints) {
    auto plane = Plane<float>::from_points(vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f));
    ASSERT_FLOAT_EQ(0.0f, plane.get_normal().x());
    ASSERT_FLOAT_EQ(1.0f, plane.get_normal().y());
    ASSERT_FLOAT_EQ(0.0f, plane.get_normal().z());
}

TEST_F(PlaneTestFixture, IntersectionPointRayIntersecting) {
    auto plane = Plane<float>{vec3{-1.0f, 0.0f, 0.0f}, vec3{2.0f, 0.0f, 0.0f}};
    Ray<float,3> ray{vec3{0.0f, 0.0f, 0.0f}, vec3{1.0f, 0.0f, 0.0f}};
    std::optional<vec3> intersection_point = plane.intersection_point(ray);
    ASSERT_EQ(intersection_point, vec3(2.0f, 0.0f, 0.0f));
}

TEST_F(PlaneTestFixture, IntersectionPointRayParallel) {
    auto plane = Plane<float>{vec3{-1.0f, 0.0f, 0.0f}, vec3{2.0f, 0.0f, 0.0f}};
    Ray<float,3> ray{vec3{1.0f, 1.0f, 0.0f}, vec3{0.0f, 1.0f, 0.0f}};
    std::optional<vec3> intersection_point = plane.intersection_point(ray);
    ASSERT_EQ(intersection_point, std::nullopt);
}
