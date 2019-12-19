//
//  boundingbox_tests.hpp
//  glMath
//
//  Created by Mateusz Stompór on 17/12/2019.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
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
    ASSERT_FLOAT_EQ(2.0, boundingBox.get_width_x());
    ASSERT_FLOAT_EQ(2.0, boundingBox.get_height_y());
    ASSERT_FLOAT_EQ(2.0, boundingBox.get_depth_z());
}

TEST_F(BoundingBoxTestFixture, OriginLocation) {
    ASSERT_FLOAT_EQ(0, boundingBox.get_origin().x());
    ASSERT_FLOAT_EQ(0, boundingBox.get_origin().y());
    ASSERT_FLOAT_EQ(0, boundingBox.get_origin().z());
}
