//
//  surface_triangle_tests.hpp
//  glMath
//
//  Created by Mateusz Stompór on 20/12/2019.
//  Copyright © 2019 Mateusz Stompór. All rights reserved.
//

#pragma once

#include <gtest/gtest.h>
#include <glMath/glMath.h>


class SurfaceTriangleTestFixture: public ::testing::Test {
};

TEST_F(SurfaceTriangleTestFixture, InitializationVertices) {
    std::array<vec3, 3> vertices {vec3(0.0f, 0.0f, 1.0f),
                                  vec3(1.0f, 0.0f, 1.0f),
                                  vec3(1.0f, 1.0f, 1.0f)};
    triangle3f triangle{vertices, vec3(0.0f, 0.0f, -1.0f)};
    ASSERT_EQ(triangle.vertices[0], vec3(0.0f, 0.0f, 1.0f));
    ASSERT_EQ(triangle.vertices[1], vec3(1.0f, 0.0f, 1.0f));
    ASSERT_EQ(triangle.vertices[2], vec3(1.0f, 1.0f, 1.0f));
}

TEST_F(SurfaceTriangleTestFixture, InitializationNormal) {
    std::array<vec3, 3> vertices {vec3(0.0f, 0.0f, 1.0f),
                                  vec3(1.0f, 0.0f, 1.0f),
                                  vec3(1.0f, 1.0f, 1.0f)};
    triangle3f triangle{vertices, vec3(0.0f, 0.0f, -1.0f)};
    ASSERT_EQ(triangle.normal, vec3(0.0f, 0.0f, -1.0f));
}

TEST_F(SurfaceTriangleTestFixture, IntersectionDistanceFirstVertex) {
    std::array<vec3, 3> vertices {vec3(0.0f, 0.0f, 2.0f),
                                  vec3(1.0f, 0.0f, 3.0f),
                                  vec3(1.0f, 1.0f, 4.0f)};
    triangle3f triangle{vertices, vec3(0.0f, 0.0f, -1.0f)};
    ray3f ray (vec3(0,0,0), vec3(0,0, 1));
    ASSERT_EQ(triangle.intersection_distance(ray), 2);
}

TEST_F(SurfaceTriangleTestFixture, IntersectionDistanceSecondVertex) {
    auto v0 = vec3{0.0f, 0.0f, 2.0f};
    auto v1 = vec3{1.0f, 0.0f, 3.0f};
    auto v2 = vec3{1.0f, 1.0f, 4.0f};
    std::array<vec3, 3> vertices {v0, v1, v2};
    auto normal = (v0 - v1).cross(v2 - v1).normalized();
    triangle3f triangle{vertices, normal};
    ray3f ray (vec3(1,1,0), vec3(0,0, 1));
    ASSERT_EQ(triangle.intersection_distance(ray), 4);
}

TEST_F(SurfaceTriangleTestFixture, IntersectionPoint) {
    std::array<vec3, 3> vertices {vec3(0.0f, 0.0f, 2.0f),
                                  vec3(1.0f, 0.0f, 2.0f),
                                  vec3(1.0f, 1.0f, 2.0f)};
    triangle3f triangle{vertices, vec3(0.0f, 0.0f, -1.0f)};
    ray3f ray (vec3(0,0,0), vec3(0,0, 1));
    ASSERT_EQ(triangle.intersection_point(ray), vec3(0.0f, 0.0f, 2.0f));
}