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
      
    CPPUNIT_TEST( testEquals );
      
    CPPUNIT_TEST_SUITE_END();

  public:
      
    void setUp();
    void tearDown();
      
    void testCopyConstructor();
    void testMoveConstructor();
      
    void testMoveAssignment();
    void testCopyAssignment();
      
    void testEquals();


  };
    
}


#endif  // VECTOR_TEST_H
