//
//  matrix_tests.hpp
//  glMath
//
//  Created by Mateusz Stompór on 17/12/2019.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#pragma once

#include <gtest/gtest.h>
#include <glMath/glMath.h>

using ms::math::mat3;
using ms::math::Matrix;

class MatrixTestFixture: public ::testing::Test {
};

TEST_F(MatrixTestFixture, Constructors) {
    Matrix<float, 3, 3> m(1);
    Matrix<float, 2, 4> m1(2);
    for(int i = 0; i < 9; ++i)
        ASSERT_EQ(m[i], 1.0f);
    for(int i = 0; i < 8; ++i)
        ASSERT_EQ(m1[i], 2.0f);
}

TEST_F(MatrixTestFixture, Addition) {
    Matrix<float, 3, 3> m1(1);
    Matrix<float, 3, 3> m2(2);
    Matrix<float, 3, 3> result = m1 + m2;
    for(auto i = 0; i < 9; ++i)
        ASSERT_EQ(result[i], 3.0f);
}

TEST_F(MatrixTestFixture, Subtraction) {
    Matrix<float, 3, 3> m1(1);
    Matrix<float, 3, 3> m2(2);
    Matrix<float, 3, 3> result = m1 - m2;
    for(auto i = 0; i < 9; ++i)
        ASSERT_EQ(result[i], -1.0f);
}

TEST_F(MatrixTestFixture, Equality) {
    Matrix<float, 3, 3> m1(1);
    Matrix<float, 3, 3> m2(2);
    auto mat3f = Matrix<float, 3, 3>::identity();
    ASSERT_NE(m1, m2);
    m1 = m2;
    ASSERT_EQ(m1, m2);
    m1[8] = 3.0f;
    ASSERT_NE(m1, m2);
    for(int i = 0; i < 9; ++i) {
        ASSERT_FLOAT_EQ(ms::math::mat3::identity()[i], (mat3f * mat3f)[i]);
    }
}

TEST_F(MatrixTestFixture, Multiplication) {
    Matrix<float, 2, 2> m1(1);
    Matrix<float, 2, 2> m2(2);
    auto result1 = m1 * m2;
    for(int i = 0; i < 4; ++i)
        ASSERT_EQ(result1[i],4.0f);
    Matrix<float, 2, 3> m3(1);
    Matrix<float, 3, 4> m4(2);
    auto result2 = m3 * m4;
    for(int i = 0; i < 8; ++i)
        ASSERT_EQ(result2[i], 6.0f);
    m1 *= m2;
    for(int i = 0; i < 8; ++i)
        ASSERT_EQ(result2[i], 6.0f);
    auto identity = Matrix<float, 2, 2>::identity();
    identity *= identity;
    ASSERT_EQ(identity, (Matrix<float, 2, 2>::identity()) * (Matrix<float, 2, 2>::identity()));
}

TEST_F(MatrixTestFixture, DiagonalMatrices) {
    auto identity = ms::math::Matrix<float, 2, 2>::identity();
    for(int i = 0; i < 2; ++i)
        for(int j = 0; j < 2; ++j)
            ASSERT_EQ(identity[i * 2 + j], (j == i ? 1 : 0));

    auto diagonal = ms::math::Matrix<float, 4, 4>::diagonal(34);
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            ASSERT_EQ(diagonal[i * 4 + j], (j == i ? 34 : 0));
}

TEST_F(MatrixTestFixture, Transposition) {
    auto identity = ms::math::Matrix<float, 2, 2>::identity().transposition();
    ASSERT_EQ(identity, (ms::math::Matrix<float, 2, 2>::identity()));
    auto mat24 = ms::math::Matrix<float, 2, 4>(2);
    auto mat42 = ms::math::Matrix<float, 4, 2>(1);
    ASSERT_EQ((mat42*2), mat24.transposition());
    ms::math::Matrix<float, 2, 2> mat;
    mat[0] = 1;
    mat[1] = 3;
    mat[2] = 2;
    mat[3] = 4;
    auto mat2 = mat.transposition();
    ASSERT_EQ(mat2[0], 1);
    ASSERT_EQ(mat2[1], 2);
    ASSERT_EQ(mat2[2], 3);
    ASSERT_EQ(mat2[3], 4);
}

TEST_F(MatrixTestFixture, Scaling3D) {
    float tab [] = {1.0f, 1.0f, 1.0f};
    Vector<float, 3> vec(tab);
    auto scale = ms::math::transform::scale<float, 3>(vec2(1, 2));
    auto result = scale * vec;
    ASSERT_FLOAT_EQ(1.0, result[0]);
    ASSERT_FLOAT_EQ(2.0, result[1]);
    ASSERT_FLOAT_EQ(1.0, result[2]);
}

TEST_F(MatrixTestFixture, Scaling4D) {
    float tab2 [] = {1.0f, 1.0f, 1.0f, 1.0f};
    Vector<float, 4> vec2(tab2);
    auto scale2 = ms::math::transform::scale<float, 4>({1, 2, 3});
    auto result2 = vec2 * scale2;
    ASSERT_FLOAT_EQ(1.0, result2[0]);
    ASSERT_FLOAT_EQ(2.0, result2[1]);
    ASSERT_FLOAT_EQ(3.0, result2[2]);
    ASSERT_FLOAT_EQ(1.0, result2[3]);
    ASSERT_FLOAT_EQ(1.0, result2.x());
    ASSERT_FLOAT_EQ(2.0, result2.y());
    ASSERT_FLOAT_EQ(3.0, result2.z());
    ASSERT_FLOAT_EQ(1.0, result2.w());
}

TEST_F(MatrixTestFixture, Translation3D) {
    float tab [] = { 1.0f, 1.0f, 1.0f };
    Vector<float, 3> vec(tab);
    auto scale = ms::math::transform::translate<float, 3>({2, 0});
    auto result = vec * scale;
    ASSERT_FLOAT_EQ(3.0, result[0]);
    ASSERT_FLOAT_EQ(1.0, result[1]);
    scale = ms::math::transform::translate<float, 3>({0, 2});
    result = result * scale;
    ASSERT_FLOAT_EQ(3.0, result[0]);
    ASSERT_FLOAT_EQ(3.0, result[1]);
    scale = ms::math::transform::translate<float, 3>({0, 2});
    result = result * scale;
    ASSERT_FLOAT_EQ(3.0, result[0]);
    ASSERT_FLOAT_EQ(5.0, result[1]);
}

TEST_F(MatrixTestFixture, Translation4D) {
    float tab [] = { 1.0f, 1.0f, 1.0f, 1.0f};
    Vector<float, 4> vec(tab);
    auto scale = ms::math::transform::translate<float, 4>({2, 0, 0});
    auto result = vec * scale;
    ASSERT_FLOAT_EQ(3.0, result[0]);
    ASSERT_FLOAT_EQ(1.0, result[1]);
    ASSERT_FLOAT_EQ(1.0, result[2]);
    ASSERT_FLOAT_EQ(1.0, result[3]);
    scale = ms::math::transform::translate<float, 4>({0, 3, 0.1});
    result = scale * result;
    ASSERT_FLOAT_EQ(3.0, result[0]);
    ASSERT_FLOAT_EQ(4.0, result[1]);
    ASSERT_FLOAT_EQ(1.1, result[2]);
    ASSERT_FLOAT_EQ(1.0, result[3]);
}

TEST_F(MatrixTestFixture, TransformationConversion) {
    mat4 translation = translate<float, 4>({3.0f, 2.0f, 1.0f});
    mat4 scaleMat = scale<float, 4>(vec3(3.0f, 2.0f, 1.0f));
    translation = scaleMat * translation;
    vec3 position = get_position(translation);
    ASSERT_FLOAT_EQ(position[0], 9.0f);
    ASSERT_FLOAT_EQ(position[1], 4.0f);
    ASSERT_FLOAT_EQ(position[2], 1.0f);
}

TEST_F(MatrixTestFixture, Rotations) {
    float tab [] = { 1.0f, 1.0f, 1.0f };
    Vector<float, 3> vec(tab);
    auto rotation = ms::math::transform::rotate_about_x_radians<float, 3>(M_PI);
    auto result = vec * rotation;
    ASSERT_FLOAT_EQ(1.0, result[0]);
    ASSERT_FLOAT_EQ(-1.0, result[1]);
    ASSERT_FLOAT_EQ(-1.0, result[2]);
    result = result * rotation;
    ASSERT_FLOAT_EQ(1.0, result[0]);
    ASSERT_FLOAT_EQ(1.0, result[1]);
    ASSERT_FLOAT_EQ(1.0, result[2]);
    rotation = ms::math::transform::rotate_about_y_radians<float, 3>(M_PI);
    result = result * rotation;
    ASSERT_FLOAT_EQ(-1.0, result[0]);
    ASSERT_FLOAT_EQ(1.0, result[1]);
    ASSERT_FLOAT_EQ(-1.0, result[2]);
    result = result * rotation;
    ASSERT_FLOAT_EQ(1.0, result[0]);
    ASSERT_FLOAT_EQ(1.0, result[1]);
    ASSERT_FLOAT_EQ(1.0, result[2]);
    rotation = ms::math::transform::rotate_about_z_radians<float, 3>(M_PI);
    result = result * rotation;
    ASSERT_FLOAT_EQ(-1.0, result[0]);
    ASSERT_FLOAT_EQ(-1.0, result[1]);
    ASSERT_FLOAT_EQ(1.0, result[2]);
    result = result * rotation;
    ASSERT_FLOAT_EQ(1.0, result[0]);
    ASSERT_FLOAT_EQ(1.0, result[1]);
    ASSERT_FLOAT_EQ(1.0, result[2]);
    float tab3 [] = { 0.0f, 0.0f, 1.0f };
    rotation = ms::math::transform::rotate_about_axis<float, 3>(M_PI, ms::math::Vector<float, 3>(tab3));
    result = result * rotation;
    ASSERT_FLOAT_EQ(-1.0, result[0]);
    ASSERT_FLOAT_EQ(-1.0, result[1]);
    ASSERT_FLOAT_EQ(1.0, result[2]);
    result = result * rotation;
    ASSERT_FLOAT_EQ(1.0, result[0]);
    ASSERT_FLOAT_EQ(1.0, result[1]);
    ASSERT_FLOAT_EQ(1.0, result[2]);
    float tab4 [] = { 1.0f, 0.0f, 0.0f };
    rotation = ms::math::transform::rotate_about_axis<float, 3>(M_PI, ms::math::Vector<float, 3>(tab4));
    result = result * rotation;
    ASSERT_FLOAT_EQ(1.0, result[0]);
    ASSERT_FLOAT_EQ(-1.0, result[1]);
    ASSERT_FLOAT_EQ(-1.0, result[2]);
    float tab5 [] = { 5.0f, 0.0f, 0.0f };
    rotation = ms::math::transform::rotate_about_axis<float, 3>(M_PI, ms::math::Vector<float, 3>(tab5).normalized());
    ms::math::projection::perspective<float>(0.1, 100, 90, 16.0/9.0);
    result = result * rotation;
    ASSERT_FLOAT_EQ(1.0, result[0]);
    ASSERT_FLOAT_EQ(1.0, result[1]);
    ASSERT_FLOAT_EQ(1.0, result[2]);
}
