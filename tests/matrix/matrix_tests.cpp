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
