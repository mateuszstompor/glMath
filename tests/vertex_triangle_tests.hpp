//
//  vertex_triangle_tests.hpp
//  glMath
//
//  Created by Mateusz Stompór on 26/12/2019.
//  Copyright © 2019 Mateusz Stompór. All rights reserved.
//

#pragma once

#include <gtest/gtest.h>
#include <glMath/glMath.h>


class VertexTriangleTestFixture: public ::testing::Test {
};

TEST_F(VertexTriangleTestFixture, InitializationVerticesNormals) {
vtriangle3f triangle({vertex3f{vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 0.0f, 1.0f)},
                      vertex3f{vec3(0.0f, 0.0f, -1.0f), vec3(1.0f, 0.0f, 1.0f)},
                      vertex3f{vec3(0.0f, 0.0f, -1.0f), vec3(1.0f, 1.0f, 1.0f)}});
ASSERT_EQ(triangle.vertices[0].normal, vec3(0.0f, 0.0f, -1.0f));
ASSERT_EQ(triangle.vertices[1].normal, vec3(0.0f, 0.0f, -1.0f));
ASSERT_EQ(triangle.vertices[2].normal, vec3(0.0f, 0.0f, -1.0f));
}

TEST_F(VertexTriangleTestFixture, InitializationVerticesPositions) {
    vtriangle3f triangle({vertex3f{vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 0.0f, 1.0f)},
                          vertex3f{vec3(0.0f, 0.0f, -1.0f), vec3(1.0f, 0.0f, 1.0f)},
                          vertex3f{vec3(0.0f, 0.0f, -1.0f), vec3(1.0f, 1.0f, 1.0f)}});
    ASSERT_EQ(triangle.vertices[0].position, vec3(0.0f, 0.0f, 1.0f));
    ASSERT_EQ(triangle.vertices[1].position, vec3(1.0f, 0.0f, 1.0f));
    ASSERT_EQ(triangle.vertices[2].position, vec3(1.0f, 1.0f, 1.0f));
}

TEST_F(VertexTriangleTestFixture, IntersectionDistanceSecondVertex) {
    auto v0 = vec3{0.0f, 0.0f, 2.0f};
    auto v1 = vec3{1.0f, 0.0f, 3.0f};
    auto v2 = vec3{1.0f, 1.0f, 4.0f};
    auto normal = (v0 - v1).cross(v2 - v1).normalized();
    std::array<vertex3f , 3> vertices {vertex3f{normal, v0},
                                       vertex3f{normal, v1},
                                       vertex3f{normal, v2}};
    vtriangle3f triangle{vertices};
    ray3f ray (vec3(1,1,0), vec3(0,0, 1));
    ASSERT_EQ(triangle.intersection_distance(ray), 4);
}

TEST_F(VertexTriangleTestFixture, IntersectionPoint) {
    std::array<vertex3f, 3> vertices {{{vec3{0, 0, -1}, vec3{0, 0, 2}},
                                       {vec3{0, 0, -1}, vec3{1, 0, 2}},
                                       {vec3{0, 0, -1}, vec3{1, 1, 2}}}};
    vtriangle3f triangle{vertices};
    ray3f ray (vec3(0,0,0), vec3(0,0, 1));
    ASSERT_EQ(triangle.intersection_point(ray), vec3(0.0f, 0.0f, 2.0f));
}
