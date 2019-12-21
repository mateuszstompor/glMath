//
//  sphere_tests.hpp
//  glMath
//
//  Created by Mateusz Stompór on 19/12/2019.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#pragma once

#include <glMath/glMath.h>

using namespace ms::math;

class SphereTestFixture: public ::testing::Test {
};

TEST_F(SphereTestFixture, InitializationRadius) {
    auto sphere = ms::math::Sphere(vec3(4.0f, 5.0f, 6.0f), 3.0f);
    ASSERT_EQ(3, sphere.radius);
}

TEST_F(SphereTestFixture, InitializationCenter) {
    auto sphere = ms::math::Sphere(vec3(4.0f, 5.0f, 6.0f), 3.0f);
    ASSERT_EQ(vec3(4, 5, 6), sphere.center);
}

TEST_F(SphereTestFixture, IntersectionDistanceRayNotHittingSphere) {
    ray3f ray {vec3(0.0f, 1.0f, -2.0f), vec3(0.0f, 0.0f, 1.0f)};
    Sphere sphere (vec3(0.0f, 4.0f, 0.0f), 2.0f);
    ASSERT_EQ(sphere.intersection_distances(ray).size(), 0);
}

TEST_F(SphereTestFixture, IntersectionDistanceRayHittingSphereOnce) {
    ray3f ray {vec3(0.0f, 2.0f, -2.0f), vec3(0.0f, 0.0f, 1.0f)};
    Sphere sphere (vec3(0.0f, 4.0f, 0.0f), 2.0f);
    ASSERT_EQ(sphere.intersection_distances(ray)[0], 2);
}

TEST_F(SphereTestFixture, IntersectionDistanceRayHittingSphereTwice) {
    ray3f ray {vec3(0.0f, 0.0f, -4.0f), vec3(0.0f, 0.0f, 1.0f)};
    Sphere sphere (vec3(0.0f, 0.0f, 0.0f), 2.0f);
    ASSERT_EQ(sphere.intersection_distances(ray)[0], 2);
    ASSERT_EQ(sphere.intersection_distances(ray)[1], 6);
}

TEST_F(SphereTestFixture, IntersectionPointsNoIntersections) {
    ray3f ray {vec3(0.0f, 1.0f, -2.0f), vec3(0.0f, 0.0f, 1.0f)};
    Sphere sphere (vec3(0.0f, 4.0f, 0.0f), 2.0f);
    ASSERT_EQ(sphere.intersection_points(ray).size(), 0);
}

TEST_F(SphereTestFixture, IntersectionPointsOneIntersection) {
    ray3f ray {vec3(0.0f, 2.0f, -2.0f), vec3(0.0f, 0.0f, 1.0f)};
    Sphere sphere (vec3(0.0f, 4.0f, 0.0f), 2.0f);
    ASSERT_EQ(sphere.intersection_points(ray)[0], vec3(0.0f, 2.0f, 0.0f));
}

TEST_F(SphereTestFixture, IntersectionPointsTwoIntersections) {
    ray3f ray {vec3(0.0f, 0.0f, -4.0f), vec3(0.0f, 0.0f, 1.0f)};
    Sphere sphere (vec3(0.0f, 0.0f, 0.0f), 2.0f);
    ASSERT_EQ(sphere.intersection_points(ray).size(), 2);
    ASSERT_EQ(sphere.intersection_points(ray)[0], vec3(0.0f, 0.0f, -2.0f));
    ASSERT_EQ(sphere.intersection_points(ray)[1], vec3(0.0f, 0.0f, 2.0f));
}
