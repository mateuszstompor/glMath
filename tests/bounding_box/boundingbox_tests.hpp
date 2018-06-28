#ifndef BOUNDING_BOX_TEST_H
#define BOUNDING_BOX_TEST_H

#include <cppunit/extensions/HelperMacros.h>

#include <glMath/glMath.h>

using namespace ms;
using namespace ms::math;
using namespace ms::math::transform;

namespace ms {
    
  class BoundingBoxTest : public CppUnit::TestFixture {
	  CPPUNIT_TEST_SUITE( BoundingBoxTest );
	
	  CPPUNIT_TEST( testPlaneIntersection );
	  CPPUNIT_TEST( testBasicInitialization );

	  CPPUNIT_TEST_SUITE_END();

  public:
	
	  void setUp();
	  void tearDown();
	  void testBasicInitialization();
	  void testPlaneIntersection();
	  
	  
  private:
	  
	  BoundingBox<float> bb0 {0, 1, 0, 1, 0, 1};
	  BoundingBox<float> bb1 {-1, 1, -1, 1, -1, 1};
	  Plane<float> p{vec3{0, 1, 0}, vec3{0, 0, 0}};
  
  };
    
}


#endif // BOUNDING_BOX_TEST_H
