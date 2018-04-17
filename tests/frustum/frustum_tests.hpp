#ifndef FRUSTUM_TEST_H
#define FRUSTUM_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cstdlib>
#include <iostream>
#include <ctime>

#include "../../source/glMath.h"
#include "../helper.h"

using namespace ms;
using namespace ms::math;
using namespace ms::math::transform;

namespace ms {
    
  class FrustumTest : public CppUnit::TestFixture {
	 
	  CPPUNIT_TEST_SUITE(FrustumTest);
	  CPPUNIT_TEST(frustumInitialization);
	  CPPUNIT_TEST(measureTestingPerformance);
	  CPPUNIT_TEST(measureInitializationPerformance);
	  CPPUNIT_TEST_SUITE_END();

  public:
	
	  void setUp();
	  void tearDown();
	  void measureTestingPerformance();
	  void measureInitializationPerformance();
	  void frustumInitialization();
  };
    
}


#endif  // FRUSTUM_TEST_H
