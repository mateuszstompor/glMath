#ifndef VECTOR_TEST_H
#define VECTOR_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include <memory>

#include "../source/vector.h"

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
      
    CPPUNIT_TEST_SUITE_END();

  public:
      
    void setUp();
    void tearDown();
      
    void testCopyConstructor();
    void testMoveConstructor();
      
    void testMoveAssignment();
    void testCopyAssignment();
      
    void testLength();
      
    void testAddition();
	  
	void testDot();
	void testCross();
	void testNormalization();
      
    void testComponentsAccess();
      
    void testScalarMultiplication();
      
    void testSubtraction();
      
    void testEquals();


  };
    
}


#endif  // VECTOR_TEST_H
