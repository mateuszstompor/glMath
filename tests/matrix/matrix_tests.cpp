#include "matrix_tests.hpp"

using namespace ms;

CPPUNIT_TEST_SUITE_REGISTRATION(MatrixTest);

void MatrixTest::setUp() {
    
}

void MatrixTest::tearDown() {

}

void MatrixTest::testConstructors() {
	
	ms::math::Matrix<float, 3, 3> m(1);
	for(int i = 0; i < 9; ++i)
		CPPUNIT_ASSERT(m[i] == 1.0f);
	
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
