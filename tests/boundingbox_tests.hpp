//
// Created by Mateusz Stompór on 17/12/2019.
//

#pragma once

#include <gtest/gtest.h>
#include <glMath/glMath.h>

using namespace ms::math;

class BoundingBoxTestFixture: public ::testing::Test {
  protected:
	  BoundingBox<float> boundingBox {-1, 1, -1, 1, -1, 1};
	  Plane<float> plane {vec3{0, 1, 0}, vec3{0, 0, 0}};
};

TEST_F(BoundingBoxTestFixture, Dimensions) {
    ASSERT_NEAR(2.0, boundingBox.get_width_x(), 0.00001);
    ASSERT_NEAR(2.0, boundingBox.get_height_y(), 0.00001);
    ASSERT_NEAR(2.0, boundingBox.get_depth_z(), 0.00001);
}

TEST_F(BoundingBoxTestFixture, OriginLocation) {
    ASSERT_NEAR(0, boundingBox.get_origin().x(), 0.00001);
    ASSERT_NEAR(0, boundingBox.get_origin().y(), 0.00001);
    ASSERT_NEAR(0, boundingBox.get_origin().z(), 0.00001);
}
