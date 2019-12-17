#pragma once

#include <gtest/gtest.h>
#include <glMath/glMath.h>

using namespace ms::math;
using namespace ms::math::transform;

class FrustumTestFixture: public ::testing::Test {
};

TEST_F(FrustumTestFixture, CameraSight) {
    FrustumViewport<float> f{0.01f, 100.0f, 90.0f, 16.0f/9.0f};
    OrthographicViewport<float> o{1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f};
    BoundingBox<float> b{-0.5f, 0.5f, -0.5f, 0.5f, -0.5f, 0.5f};

    ASSERT_FALSE(f.is_in_camera_sight(translate<float, 4>(vec3{0.0f, 0.0f, 200.0f}), b));
    ASSERT_FALSE(f.is_in_camera_sight(translate<float, 4>(vec3{0.0f, 0.0f, 120.0f}), b));
    ASSERT_TRUE(f.is_in_camera_sight(mat4::identity(), b));
    ASSERT_TRUE(o.is_in_camera_sight(mat4::identity(), b));

    // Top outside
    ASSERT_TRUE(o.is_in_camera_sight(translate<float, 4>(vec3{0.0f, 1.49f, 0.0f}), b));
    ASSERT_FALSE(o.is_in_camera_sight(translate<float, 4>(vec3{0.0f, 1.61f, 0.0f}), b));

    // Bottom outside
    ASSERT_TRUE(o.is_in_camera_sight(translate<float, 4>(vec3{0.0f, -1.49f, 0.0f}), b));
    ASSERT_FALSE(o.is_in_camera_sight(translate<float, 4>(vec3{0.0f, -1.6f, 0.0f}), b));
    // Left outside
    ASSERT_TRUE(o.is_in_camera_sight(translate<float, 4>(vec3{-1.49f, 0.0f, 0.0f}), b));
    ASSERT_FALSE(o.is_in_camera_sight(translate<float, 4>(vec3{-1.60f, 0.0f, 0.0f}), b));
    // Right outside
    ASSERT_TRUE(o.is_in_camera_sight(translate<float, 4>(vec3{1.49f, 0.0f, 0.0f}), b));
    ASSERT_FALSE(o.is_in_camera_sight(translate<float, 4>(vec3{1.6f, 0.0f, 0.0f}), b));
    // Front outside
    ASSERT_TRUE(o.is_in_camera_sight(translate<float, 4>(vec3{0.0f, -1.49f, 0.0f}), b));
    ASSERT_FALSE(o.is_in_camera_sight(translate<float, 4>(vec3{0.0f, -1.6f, 0.0f}), b));
    // Back outside
    ASSERT_TRUE(o.is_in_camera_sight(translate<float, 4>(vec3{0.0f, 0.0f, 1.49f}), b));
    ASSERT_FALSE(o.is_in_camera_sight(translate<float, 4>(vec3{0.0f, 0.0f, 1.6f}), b));
}
