#include "plane_tests.hpp"

using namespace ms;
using namespace math;

CPPUNIT_TEST_SUITE_REGISTRATION(PlaneTest);

void PlaneTest::setUp() {
    
}

void PlaneTest::tearDown() {

}

void PlaneTest::testIsInFront() {
	const BoundingBox<float> bb0 (0, 1, 0, 1, 0, 1);
	const BoundingBox<float> bb1 (-2, 1, -2, 1, -2, 1);

	const Plane<float> p0(vec3(0, 1, 0), vec3(0, -1, 0));
	
	
	CPPUNIT_ASSERT(p0.is_in_front(bb0));
	CPPUNIT_ASSERT(!p0.is_in_front(bb1));
	
	const Plane<float> p1 = Plane<float>::from_points(vec3(4,2, 2), vec3(2,2,2), vec3(2,-1,2));
	
	const Plane<float> p2 (vec3(0,0,-1), vec3(0,0,100));

	CPPUNIT_ASSERT(p2.is_in_front(bb0));
	
	CPPUNIT_ASSERT(p1.is_in_front(bb0));
	CPPUNIT_ASSERT(p1.get_position(bb0) == Plane<float>::RelativePosition::in_front);

}

void PlaneTest::testRelativePosition() {
	BoundingBox<float> bb0 (0, 1, 0, 1, 0, 1);
	BoundingBox<float> bb1 (-2, 1, -2, 1, -2, 1);

	Plane<float> p0(vec3(0, 1, 0), vec3(0, -1, 0));
	Plane<float> p1(vec3(0, 1, 0), vec3(0, 2, 0));



	CPPUNIT_ASSERT(p0.get_position(bb0) == ms::math::Plane<float>::RelativePosition::in_front);
	CPPUNIT_ASSERT(p0.get_position(bb1) == ms::math::Plane<float>::RelativePosition::intersects);
	CPPUNIT_ASSERT(p1.get_position(bb0) == ms::math::Plane<float>::RelativePosition::behind);
}

void PlaneTest::testCreationFromThreePoints() {
	
	auto plane = Plane<float>::from_points(vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f));

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, plane.get_normal().x(), 0.001f);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, plane.get_normal().y(), 0.001f);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, plane.get_normal().z(), 0.001f);
}
