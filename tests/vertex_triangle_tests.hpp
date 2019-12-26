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