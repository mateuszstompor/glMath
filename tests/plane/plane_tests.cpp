#include "plane_tests.hpp"

using namespace ms;
using namespace math;

CPPUNIT_TEST_SUITE_REGISTRATION(PlaneTest);

void PlaneTest::setUp() {
    
}

void PlaneTest::tearDown() {

}

void PlaneTest::testIsInFront() {
	BoundingBox<float> bb0 {0, 1, 0, 1, 0, 1};
	BoundingBox<float> bb1 {-2, 1, -2, 1, -2, 1};

	Plane<float> p0{vec3{0, 1, 0}, vec3{0, -1, 0}, vec3{0, -1, 1}};
	
	
	CPPUNIT_ASSERT(p0.is_in_front(bb0));
	CPPUNIT_ASSERT(!p0.is_in_front(bb1));
}

void PlaneTest::testPlaneCorrectness() {
	Plane<float> p0{vec3{0, 1, 0}, vec3{0, 0, 0}, vec3{0, 0, 1}};
	Plane<float> p1{vec3{0, 1, 0}, vec3{0, 0, 0}, vec3{0, 1, 0}};
	
	CPPUNIT_ASSERT(p0.is_valid());
	CPPUNIT_ASSERT(!p1.is_valid());
}

void PlaneTest::testRelativePosition() {
	BoundingBox<float> bb0 {0, 1, 0, 1, 0, 1};
	BoundingBox<float> bb1 {-2, 1, -2, 1, -2, 1};
	
	Plane<float> p0{vec3{0, 1, 0}, vec3{0, -1, 0}, vec3{0, -1, 1}};
	Plane<float> p1{vec3{0, 1, 0}, vec3{0, 2, 0}, vec3{1, 2, 0}};
	
	CPPUNIT_ASSERT(p0.get_position(bb0) == ms::math::Plane<float>::RelativePosition::in_front);
	CPPUNIT_ASSERT(p0.get_position(bb1) == ms::math::Plane<float>::RelativePosition::intersects);
	CPPUNIT_ASSERT(p1.get_position(bb0) == ms::math::Plane<float>::RelativePosition::behind);

}

void PlaneTest::testCreationFromThreePoints() {
	vec3 firstPoint(1.0f, 0.0f, 0.0f);
	vec3 secondPoint(0.0f, 0.0f, -1.0f);
	vec3 origin(0.0f, 0.0f, 0.0f);
	
	auto plane = Plane<float>::from_points(firstPoint, origin, secondPoint);
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, plane.get_normal().x(), 0.001f);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, plane.get_normal().y(), 0.001f);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, plane.get_normal().z(), 0.001f);
	
}
