#ifndef VECTOR_TEST_H
#define VECTOR_TEST_H

#include <cppunit/extensions/HelperMacros.h>

#include <chrono>

#include "../../source/glMath.h"

template<typename T>
inline long measure_time(std::function<void(void)> lambda) {
	auto start = std::chrono::high_resolution_clock::now();
	lambda();
	auto now = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<T>(now - start).count();
}

namespace ms {
    
  class VectorTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE( VectorTest );

    CPPUNIT_TEST( testCopyConstructor );
    CPPUNIT_TEST( testMoveConstructor );
    
    CPPUNIT_TEST( testCopyAssignment );
    CPPUNIT_TEST( testMoveAssignment );
      
    CPPUNIT_TEST( testLength );
    CPPUNIT_TEST( testAddition );
	CPPUNIT_TEST( testDot );
	CPPUNIT_TEST( testCross );
	CPPUNIT_TEST( testNormalization );
    CPPUNIT_TEST( testComponentsAccess );
    CPPUNIT_TEST( testScalarMultiplication );
    CPPUNIT_TEST( testSubtraction );
    CPPUNIT_TEST( testEquals );
	CPPUNIT_TEST( testMatrixMult );
	CPPUNIT_TEST( testSphericalCoordinatesConversionDegrees );
	CPPUNIT_TEST( testSphericalCoordinatesConversionRadians );
	CPPUNIT_TEST( testDimensionChange );
	CPPUNIT_TEST( testPerformance );

    CPPUNIT_TEST_SUITE_END();

  public:
      
    void setUp();
    void tearDown();
      
    void testCopyConstructor();
    void testMoveConstructor();
	void testDimensionChange();
      
    void testMoveAssignment();
    void testCopyAssignment();
      
    void testLength();
	  
	void testMatrixMult();
	  
    void testAddition();
	  
	void testDot();
	void testCross();
	void testNormalization();
	  
	void testSphericalCoordinatesConversionDegrees();
	void testSphericalCoordinatesConversionRadians();
	  
    void testComponentsAccess();
      
    void testScalarMultiplication();
      
    void testSubtraction();
	  
	void testPerformance();
      
    void testEquals();


  };
    
}


#endif  // VECTOR_TEST_H
