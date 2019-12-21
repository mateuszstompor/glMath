//
//  triangle_tests.hpp
//  glMath
//
//  Created by Mateusz Stompór on 20/12/2019.
//  Copyright © 2019 Mateusz Stompór. All rights reserved.
//

#include <gtest/gtest.h>
#include <glMath/glMath.h>


class TriangleTestFixture: public ::testing::Test {
};

TEST_F(TriangleTestFixture, InitializationVertices) {
    std::array<vec3, 3> vertices {vec3(0.0f, 0.0f, 1.0f),
                                  vec3(1.0f, 0.0f, 1.0f),
                                  vec3(1.0f, 1.0f, 1.0f)};
    triangle3f triangle{vertices, vec3(0.0f, 0.0f, -1.0f)};
    ASSERT_EQ(triangle.vertices[0], vec3(0.0f, 0.0f, 1.0f));
    ASSERT_EQ(triangle.vertices[1], vec3(1.0f, 0.0f, 1.0f));
    ASSERT_EQ(triangle.vertices[2], vec3(1.0f, 1.0f, 1.0f));
}

TEST_F(TriangleTestFixture, InitializationNormal) {
    std::array<vec3, 3> vertices {vec3(0.0f, 0.0f, 1.0f),
                                  vec3(1.0f, 0.0f, 1.0f),
                                  vec3(1.0f, 1.0f, 1.0f)};
    triangle3f triangle{vertices, vec3(0.0f, 0.0f, -1.0f)};
    ASSERT_EQ(triangle.normal, vec3(0.0f, 0.0f, -1.0f));
}

TEST_F(TriangleTestFixture, IntersectionDistance) {
    std::array<vec3, 3> vertices {vec3(0.0f, 0.0f, 2.0f),
                                  vec3(1.0f, 0.0f, 2.0f),
                                  vec3(1.0f, 1.0f, 2.0f)};
    triangle3f triangle{vertices, vec3(0.0f, 0.0f, -1.0f)};
    ray3f ray (vec3(0,0,0), vec3(0,0, 1));
    ASSERT_EQ(triangle.intersection_distance(ray), 2);
}

TEST_F(TriangleTestFixture, IntersectionPoint) {
    std::array<vec3, 3> vertices {vec3(0.0f, 0.0f, 2.0f),
                                  vec3(1.0f, 0.0f, 2.0f),
                                  vec3(1.0f, 1.0f, 2.0f)};
    triangle3f triangle{vertices, vec3(0.0f, 0.0f, -1.0f)};
    ray3f ray (vec3(0,0,0), vec3(0,0, 1));
    ASSERT_EQ(triangle.intersection_point(ray), vec3(0.0f, 0.0f, 2.0f));
}