#ifndef MATRIX_TEST_H
#define MATRIX_TEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "../../source/matrix.h"

namespace ms {
    
  class MatrixTest : public CppUnit::TestFixture {
    	CPPUNIT_TEST_SUITE( MatrixTest );
	
	  CPPUNIT_TEST( testConstructors );
	  CPPUNIT_TEST( testAddition );
	  CPPUNIT_TEST( testSubtraction );
	  CPPUNIT_TEST( testEquality );

	  CPPUNIT_TEST_SUITE_END();

  public:
      
    	void setUp();
    	void tearDown();
	  
	  void testConstructors();
	  void testAddition();
	  void testSubtraction();
	  void testEquality();
  };
    
}


#endif  // MATRIX_TEST_H
