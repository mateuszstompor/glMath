#include "matrix_tests.hpp"

using namespace ms;

CPPUNIT_TEST_SUITE_REGISTRATION(MatrixTest);

void MatrixTest::setUp() {
    
}

void MatrixTest::tearDown() {

}

void MatrixTest::testConstructors() {
	
	ms::math::Matrix<float, 3, 3> m(1);
	ms::math::Matrix<float, 2, 4> m1(2);
	for(int i = 0; i < 9; ++i)
		CPPUNIT_ASSERT(m[i] == 1.0f);
	for(int i = 0; i < 8; ++i)
		CPPUNIT_ASSERT(m1[i] == 2.0f);
	
}

void MatrixTest::testAddition() {
	ms::math::Matrix<float, 3, 3> m1(1);
	ms::math::Matrix<float, 3, 3> m2(2);
	ms::math::Matrix<float, 3, 3> result;
	result = m1 + m2;
	for(int i = 0; i < 9; ++i)
		CPPUNIT_ASSERT(result[i] == 3.0f);
}

void MatrixTest::testSubtraction() {
	ms::math::Matrix<float, 3, 3> m1(1);
	ms::math::Matrix<float, 3, 3> m2(2);
	ms::math::Matrix<float, 3, 3> result;
	result = m1 - m2;
	for(int i = 0; i < 9; ++i)
		CPPUNIT_ASSERT(result[i] == -1.0f);
}

void MatrixTest::testEquality() {
	
	ms::math::Matrix<float, 3, 3> m1(1);
	ms::math::Matrix<float, 3, 3> m2(2);
	CPPUNIT_ASSERT(m1 != m2);
	m1 = m2;
	CPPUNIT_ASSERT(m1 == m2);
	m1[8] = 3.0f;
	CPPUNIT_ASSERT(m1 != m2);
}

void MatrixTest::testMultiplication() {
	ms::math::Matrix<float, 2, 2> m1(1);
	ms::math::Matrix<float, 2, 2> m2(2);
	ms::math::Matrix<float, 2, 2> result1;
	ms::math::Matrix<float, 2, 4> result2;
	
	result1 = m1 * m2;
	
	for(int i = 0; i < 4; ++i)
		CPPUNIT_ASSERT(result1[i] == 4.0f);

	ms::math::Matrix<float, 2, 3> m3(1);
	ms::math::Matrix<float, 3, 4> m4(2);

	result2 = m3 * m4;
	for(int i = 0; i < 8; ++i)
		CPPUNIT_ASSERT(result2[i] == 6.0f);
	
	m1 *= m2;
	for(int i = 0; i < 8; ++i)
		CPPUNIT_ASSERT(result2[i] == 6.0f);
	
	auto identity = ms::math::Matrix<float, 2, 2>::identity();
	identity *= identity;
	CPPUNIT_ASSERT(identity == (ms::math::Matrix<float, 2, 2>::identity()) * (ms::math::Matrix<float, 2, 2>::identity()));


}

void MatrixTest::testDiagonalMatrices() {
	
	auto identity = ms::math::Matrix<float, 2, 2>::identity();
	for(int i = 0; i < 2; ++i) {
		for(int j = 0; j < 2; ++j) {
			CPPUNIT_ASSERT(identity[i * 2 + j] == (j == i ? 1 : 0));
		}
	}
	
	auto diagonal = ms::math::Matrix<float, 4, 4>::diagonal(34);
	for(int i = 0; i < 4; ++i) {
		for(int j = 0; j < 4; ++j) {
			CPPUNIT_ASSERT(diagonal[i * 4 + j] == (j == i ? 34 : 0));
		}
	}
	
}

void MatrixTest::testTransposition() {
	
	auto identity = ms::math::Matrix<float, 2, 2>::identity().transposition();
	CPPUNIT_ASSERT(identity == (ms::math::Matrix<float, 2, 2>::identity()));

	auto mat24 = ms::math::Matrix<float, 2, 4>(2);
	auto mat42 = ms::math::Matrix<float, 4, 2>(1);
	
	CPPUNIT_ASSERT((mat42*2) == mat24.transposition());
	
	ms::math::Matrix<float, 2, 2> mat;
	mat[0] = 1;
	mat[1] = 3;
	mat[2] = 2;
	mat[3] = 4;
	
	auto mat2 = mat.transposition();
	CPPUNIT_ASSERT(mat2[0] == 1);
	CPPUNIT_ASSERT(mat2[1] == 2);
	CPPUNIT_ASSERT(mat2[2] == 3);
	CPPUNIT_ASSERT(mat2[3] == 4);

}

void MatrixTest::testScaling() {
	
	float tab [] = { 1.0f, 1.0f, 1.0f };
	
	math::Vector<float, 3> vec(tab);
	
	auto scale = ms::math::transform::scale<float, 3>({1, 2, 3});
	
	auto result = vec * scale;
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, result[0], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, result[1], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(3.0, result[2], 0.001);
	
	float tab2 [] = { 1.0f, 1.0f, 1.0f, 1.0f };
	
	math::Vector<float, 4> vec2(tab2);
	
	auto scale2 = ms::math::transform::scale<float, 4>({1, 2, 3});
	
	auto result2 = vec2 * scale2;
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, result2[0], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, result2[1], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(3.0, result2[2], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, result2[3], 0.001);
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, result2.x(), 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, result2.y(), 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(3.0, result2.z(), 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, result2.w(), 0.001);
	
}

void MatrixTest::testTranslation() {
	
	float tab [] = { 1.0f, 1.0f, 1.0f };
	
	math::Vector<float, 3> vec(tab);
	
	auto scale = ms::math::transform::translate<float, 3>({2});
	
	auto result = vec * scale;
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL(3.0, result[0], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, result[1], 0.001);
	
	scale = ms::math::transform::translate<float, 3>({0, 2});
	
	result = result * scale;
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL(3.0, result[0], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(3.0, result[1], 0.001);
	
	scale = ms::math::transform::translate<float, 3>({0, 2});
	
	result = result * scale;
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL(3.0, result[0], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(5.0, result[1], 0.001);
	
	float tab2 [] = { 1.0f, 1.0f, 1.0f, 1.0f};
	
	math::Vector<float, 4> vec2(tab2);
	
	auto scale2 = ms::math::transform::translate<float, 4>({2});
	
	auto result2 = vec2 * scale2;
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL(3.0, result2[0], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, result2[1], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, result2[2], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, result2[3], 0.001);
	
	scale2 = ms::math::transform::translate<float, 4>({0, 3, 0.1});

	result2 = scale2 * result2;
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL(3.0, result2[0], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(4.0, result2[1], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.1, result2[2], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, result2[3], 0.001);
	
}

void MatrixTest::testRotations() {
	
	float tab [] = { 1.0f, 1.0f, 1.0f };
	
	math::Vector<float, 3> vec(tab);
	
	auto rotation = ms::math::transform::rotateAboutXRadians<float, 3>(M_PI);
	
	auto result = vec * rotation;
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, result[0], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, result[1], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, result[2], 0.001);
	
	result = result * rotation;
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, result[0], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, result[1], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, result[2], 0.001);
	
	rotation = ms::math::transform::rotateAboutYRadians<float, 3>(M_PI);
	
	result = result * rotation;
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, result[0], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, result[1], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, result[2], 0.001);
	
	result = result * rotation;
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, result[0], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, result[1], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, result[2], 0.001);
	
	rotation = ms::math::transform::rotateAboutZRadians<float, 3>(M_PI);
	
	result = result * rotation;
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, result[0], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, result[1], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, result[2], 0.001);
	
	result = result * rotation;
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, result[0], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, result[1], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, result[2], 0.001);
	
	float tab3 [] = { 0.0f, 0.0f, 1.0f };
	
	rotation = ms::math::transform::rotateAboutAxis<float, 3>(M_PI, ms::math::Vector<float, 3>(tab3));
	
	result = result * rotation;
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, result[0], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, result[1], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, result[2], 0.001);
	
	result = result * rotation;
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, result[0], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, result[1], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, result[2], 0.001);
	
	float tab4 [] = { 1.0f, 0.0f, 0.0f };
	
	rotation = ms::math::transform::rotateAboutAxis<float, 3>(M_PI, ms::math::Vector<float, 3>(tab4));
	
	result = result * rotation;
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, result[0], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, result[1], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, result[2], 0.001);
	
	float tab5 [] = { 5.0f, 0.0f, 0.0f };
	
	rotation = ms::math::transform::rotateAboutAxis<float, 3>(M_PI, ms::math::Vector<float, 3>(tab5).normalized());
	
	ms::math::projection::perspective<float>(0.1, 100, 90, 16.0/9.0);
	
	result = result * rotation;
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, result[0], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, result[1], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, result[2], 0.001);
	
}

