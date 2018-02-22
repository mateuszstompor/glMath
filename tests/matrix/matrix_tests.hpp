#ifndef MATRIX_TEST_H
#define MATRIX_TEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "../../source/matrix.h"

namespace ms {
    
  class MatrixTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE( MatrixTest );

    CPPUNIT_TEST_SUITE_END();

  public:
      
    void setUp();
    void tearDown();
      
  };
    
}


#endif  // MATRIX_TEST_H
