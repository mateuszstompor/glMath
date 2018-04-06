#ifndef PLANE_TEST_H
#define PLANE_TEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "../../source/glMath.h"

using namespace ms;
using namespace ms::math;
using namespace ms::math::transform;

namespace ms {
    
  class PlaneTest : public CppUnit::TestFixture {
	  CPPUNIT_TEST_SUITE( PlaneTest );
	
	  CPPUNIT_TEST( testPlaneCorrectness );
	  CPPUNIT_TEST( testIsInFront );
	  CPPUNIT_TEST( testRelativePosition );
	  CPPUNIT_TEST( testCreationFromThreePoints );
	 
	  CPPUNIT_TEST_SUITE_END();

  public:
	
	  void setUp();
	  void tearDown();
	  void testPlaneCorrectness();
	  void testIsInFront();
	  void testRelativePosition();
	  void testCreationFromThreePoints();
	  
  protected:
	  
	  Plane<float> p{vec3{0, 1, 0}, vec3{0, 0, 0}, vec3{0, 0, 1}};

  };
    
}


#endif  // PLANE_TEST_H
