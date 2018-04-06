#ifndef MATRIX_TEST_H
#define MATRIX_TEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "../../source/glMath.h"
#include <chrono>

template<typename T>
inline long measure_time(std::function<void(void)> lambda) {
	auto start = std::chrono::high_resolution_clock::now();
	lambda();
	auto now = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<T>(now - start).count();
}


namespace ms {
    
  class MatrixTest : public CppUnit::TestFixture {
	  CPPUNIT_TEST_SUITE( MatrixTest );
	
	  CPPUNIT_TEST( testDiagonalMatrices );
	  CPPUNIT_TEST( testConstructors );
	  CPPUNIT_TEST( testAddition );
	  CPPUNIT_TEST( testSubtraction );
	  CPPUNIT_TEST( testEquality );
	  CPPUNIT_TEST( testMultiplication );
	  CPPUNIT_TEST( testMultiplicationPerformance );
	  CPPUNIT_TEST( testTransposition );
	  CPPUNIT_TEST( testScaling );
	  CPPUNIT_TEST( testTranslation );
	  CPPUNIT_TEST( testRotations );
	  CPPUNIT_TEST(	testTransformationConversion );
	  CPPUNIT_TEST_SUITE_END();

  public:
	
	  void setUp();
	  void tearDown();
	  
	  void testDiagonalMatrices();
	  void testConstructors();
	  void testAddition();
	  void testTransposition();
	  void testSubtraction();
	  void testEquality();
	  void testScaling();
	  void testRotations();
	  void testTranslation();
	  void testMultiplication();
	  void testMultiplicationPerformance();
	  void testTransformationConversion();
  
  };
    
}


#endif  // MATRIX_TEST_H
