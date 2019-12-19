//
//  vector_tests.hpp
//  glMath
//
//  Created by Mateusz Stompór on 17/12/2019.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#pragma once

#include <gtest/gtest.h>
#include <glMath/glMath.h>

using ms::math::Vector;

class VectorTestFixture: public ::testing::Test {
};

TEST_F(VectorTestFixture, CopyConstructor3D) {
    Vector<float, 3> vec1(2, 2, 2);
    Vector<float, 3> vec2(vec1);
    ASSERT_NE(vec1.c_array(), vec2.c_array());
    for (auto i = 0; i < 3; ++i) {
        ASSERT_EQ(vec1.c_array()[i], vec2.c_array()[i]);
    }
}

TEST_F(VectorTestFixture, CopyConstructor4D) {
    Vector<float, 4> vec3(2, 2, 2, 2);
    Vector<float, 4> vec4(vec3);
    ASSERT_NE(vec3.c_array(), vec4.c_array());
    for (auto i = 0; i < 4; ++i) {
        ASSERT_EQ(vec3.c_array()[i], vec4.c_array()[i]);
    }
}

TEST_F(VectorTestFixture, UnaryMinus2D) {
    Vector<float, 2> vec{2, 2};
    ASSERT_NE(-vec, vec);
    ASSERT_EQ(-(-vec[0]),  vec[0]);
    ASSERT_EQ(-(-vec[1]),  vec[1]);
}

TEST_F(VectorTestFixture, UnaryMinus3D) {
    Vector<float, 3> vec{1, 2, 3};
    ASSERT_NE(-vec, vec);
    ASSERT_EQ(-(-vec[0]),  vec[0]);
    ASSERT_EQ(-(-vec[1]),  vec[1]);
    ASSERT_EQ(-(-vec[2]),  vec[2]);
}

TEST_F(VectorTestFixture, UnaryMinusND) {
    Vector<float, 4> vec{1, 2, 3, 4};
    ASSERT_NE(-vec, vec);
    ASSERT_EQ(-(-vec[0]),  vec[0]);
    ASSERT_EQ(-(-vec[1]),  vec[1]);
    ASSERT_EQ(-(-vec[2]),  vec[2]);
    ASSERT_EQ(-(-vec[3]),  vec[3]);
}

TEST_F(VectorTestFixture, CopyAssignment) {
    Vector<float, 3> vec1(2, 2, 2);
    Vector<float, 3> vec2;
    vec2 = vec1;
    ASSERT_NE(vec2.c_array(), vec1.c_array());
    ASSERT_NE(vec1.c_array(), nullptr);
    for (auto i = 0; i < 3; ++ i) {
        ASSERT_EQ(vec1.c_array()[i], vec2.c_array()[i]);
    }
}

TEST_F(VectorTestFixture, Equals) {
    Vector<float, 3> vec1(2, 2, 2);
    Vector<float, 3> vec2(2, 2, 2);
    ASSERT_TRUE(vec2 == vec1);
    ASSERT_FALSE(vec2 != vec1);
    vec2 = Vector<float, 3>(3, 3, 3);
    ASSERT_NE(vec2, vec1);
    ASSERT_FALSE(vec2 == vec1);
}

TEST_F(VectorTestFixture, Length2D) {
    Vector<float, 2> vec{1, 0};
    ASSERT_EQ(vec.length(), 1);
}

TEST_F(VectorTestFixture, Length3D) {
    Vector<float, 3> vec(0, 3, 0);
    ASSERT_EQ(vec.length(), 3);
}

TEST_F(VectorTestFixture, Length4D) {
    Vector<float, 4> vec(3, 3, 3, 3);
    ASSERT_EQ(vec.length(), 6);
}

TEST_F(VectorTestFixture, Length5D) {
    Vector<float, 5> vec(3, 0, 0, 0, 0);
    ASSERT_EQ(vec.length(), 3);
}

TEST_F(VectorTestFixture, Addition) {
    Vector<float, 3> vec1(2, 2, 2);
    Vector<float, 3> vec2(2, 2 ,2);
    Vector<float, 3> vec3{vec1 + vec2};
    for (int i = 0; i < 3; ++ i) {
        ASSERT_EQ(vec3.c_array()[i], 4);
    }
    vec3 += vec1;
    for (int i = 0; i < 3; ++ i) {
        ASSERT_EQ(vec3.c_array()[i], 6);
    }
    for (int i = 0; i < 3; ++ i) {
        ASSERT_EQ((vec3 + vec3)[i], 12);
    }
}

TEST_F(VectorTestFixture, Subtraction) {
    Vector<float, 3> vec1(2, 2, 2);
    Vector<float, 3> vec2(2, 2, 2);
    Vector<float, 3> vec3{vec1-vec2};
    for (auto i = 0; i < 3; ++ i) {
        ASSERT_EQ(vec3.c_array()[i], 0);
    }
    vec3 -= vec1;
    for (auto i = 0; i < 3; ++ i) {
        ASSERT_EQ(vec3.c_array()[i], -2);
    }
    for (auto i = 0; i < 3; ++ i) {
        ASSERT_FLOAT_EQ((vec3 - vec3)[i], 0);
    }
    for (auto i = 0; i < 3; ++ i) {
        ASSERT_EQ((vec3 - vec3).components[i], 0);
    }
}

TEST_F(VectorTestFixture, ComponentsAccess) {
    Vector<float, 4> vec1(2, 2, 2, 2);
    for (auto i = 0; i < 4; ++ i) {
        ASSERT_EQ(vec1[i], 2);
        vec1[i] = i;
    }
    for (auto i = 0; i < 4; ++ i) {
        ASSERT_EQ(vec1[i], i);
    }
}

TEST_F(VectorTestFixture, ScalarMultiplicationAndDivision) {
    Vector<float, 3> vec1(2, 2, 2);
    Vector<float, 3> vec3 = vec1 * 2;
    vec3 *= 2;
    vec3 /= 2;
    vec3 = vec3 / 2;
    vec3 = vec3 * 2;
    for (auto i = 0; i < 3; ++ i) {
        ASSERT_EQ(vec3.c_array()[i], 4);
    }
    vec3 = 3.0f * vec1;
    for (auto i = 0; i < 3; ++ i) {
        ASSERT_EQ(vec3.c_array()[i], 6);
    }
    vec3 = operator*(2.0f, vec1);
    for (auto i = 0; i < 3; ++ i) {
        ASSERT_EQ(vec3.c_array()[i], 4);
    }
    vec3 *= 2;
    for (auto i = 0; i < 3; ++ i) {
        ASSERT_EQ(vec3.c_array()[i], 8);
    }
}

TEST_F(VectorTestFixture, Dot) {
    float tab1 [] = { 1.0f, 0.0f, 0.0f };
    float tab2 [] = { 0.0f, 1.0f, 0.0f };
    Vector<float, 3> vec1(tab1);
    Vector<float, 3> vec2(tab2);
    ASSERT_EQ(vec2.dot(vec1), 0);
}

TEST_F(VectorTestFixture, Cross) {
    float tab1 [] = { 1.0f, 2.0f, 3.0f };
    float tab2 [] = { 4.0f, 5.0f, 6.0f };
    Vector<float, 3> vec1(tab1);
    Vector<float, 3> vec2(tab2);
    Vector<float, 3> result = vec1.cross(vec2);
    ASSERT_NE(vec2.dot(vec1), 0);
    ASSERT_EQ(result[0], -3);
    ASSERT_EQ(result[1], 6);
    ASSERT_EQ(result[2], -3);
    ASSERT_EQ(vec3(1, 3, 4).cross(vec3(98, 3, 2)).x(), -6);
    ASSERT_EQ(vec3(1, 3, 4).cross(vec3(98, 3, 2)).y(), 390);
    ASSERT_EQ(vec3(1, 3, 4).cross(vec3(98, 3, 2)).z(), -291);
}

TEST_F(VectorTestFixture, Normalization) {
    float tab2 [] = { 1.0f, 1.0f, 1.0f };
    float tab3 [] = { 1.0f, 1.0f, 1.0f, 1.0f };
    Vector<float, 3> vec1(tab2);
    Vector<float, 4> vec2(tab3);
    ASSERT_NE(vec1.length(), 1);
    ASSERT_NE(vec2.length(), 1);
    vec1.normalize();
    vec2.normalize();
    auto vec3 = (vec1 * 22.0f).normalized();
    auto vec4 = (22.0f * vec2).normalized();
    ASSERT_FLOAT_EQ(1, vec1.length());
    ASSERT_FLOAT_EQ(1, vec2.length());
    ASSERT_FLOAT_EQ(1, vec3.length());
    ASSERT_FLOAT_EQ(1, vec4.length());
}

TEST_F(VectorTestFixture, MatrixMultiplication) {
    float tab2 [] = { 1.0f, 1.0f, 1.0f };
    float tab3 [] = { 4.0f, 5.0f, 6.0f };
    Vector<float, 3> vec1(tab2);
    Vector<float, 3> vec2(tab2);
    Vector<float, 3> vec3(tab3);
    mat3 mat = mat3::identity();
    auto result = vec1 * mat;
    auto result2 = vec3 * mat;
    ASSERT_EQ(result, vec1);
    mat3 mat2 = mat3::identity() * 2;
    ASSERT_EQ(vec1 * 2, vec1 * mat2);
    ASSERT_EQ(vec1 * 2,  mat2 * vec1);
    vec1 *= mat2;
    ASSERT_EQ(vec1, vec2 * mat2);
    ASSERT_EQ(result2[0], tab3[0]);
    ASSERT_EQ(result2[1], tab3[1]);
    ASSERT_EQ(result2[2], tab3[2]);
}

TEST_F(VectorTestFixture, SphericalCoordinatesConversionRadians) {
    spco::RadiansSpherical<float> co;
    co.radius = 5.0f;
    co.azimuthAngle = M_PI / 3;
    co.inclination = M_PI / 6;
    Vector<float, 3> vec1(co);
    ASSERT_FLOAT_EQ(1.25, vec1[0]);
    ASSERT_FLOAT_EQ(2.165063509, vec1[1]);
    ASSERT_FLOAT_EQ(4.330127019, vec1[2]);
    co.radius = 1.0f;
    co.azimuthAngle = 0;
    co.inclination = 0.0f;
    vec1 = Vector<float, 3>(co);
    ASSERT_FLOAT_EQ(1, co.radius);
    ASSERT_FLOAT_EQ(0, co.azimuthAngle);
    ASSERT_FLOAT_EQ(0, co.inclination);
    vec1[0] = 3.0f;
    vec1[1] = 0.0f;
    vec1[2] = 0.0f;
    co = spco::RadiansSpherical<float>(vec1);
    ASSERT_FLOAT_EQ(3, co.radius);
    ASSERT_FLOAT_EQ(0, co.azimuthAngle);
    ASSERT_FLOAT_EQ(M_PI / 2, co.inclination);
}
