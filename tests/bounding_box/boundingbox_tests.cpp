#include "boundingbox_tests.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(BoundingBoxTest);

//
//               e-------f
//              /|      /|
//             / |     / |
//            a--|----b  |
//            |  g----|--h
//            | /     | /
//            c-------d
//

void BoundingBoxTest::setUp() {
    
}

void BoundingBoxTest::tearDown() {

}

void BoundingBoxTest::testBasicInitialization() {
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, bb0.get_width_x(), 0.00001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, bb1.get_width_x(), 0.00001);
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, bb0.get_height_y(), 0.00001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, bb1.get_height_y(), 0.00001);
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, bb0.get_depth_z(), 0.00001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, bb1.get_depth_z(), 0.00001);
	
	
	auto bb0Origin = bb0.get_origin();
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5, bb0Origin.x(), 0.00001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5, bb0Origin.y(), 0.00001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5, bb0Origin.z(), 0.00001);
	
	auto bb1Origin = bb1.get_origin();
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, bb1Origin.x(), 0.00001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, bb1Origin.y(), 0.00001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, bb1Origin.z(), 0.00001);
}

void BoundingBoxTest::testPlaneIntersection() {
	
	
}
