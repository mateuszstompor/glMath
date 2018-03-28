#include "vector_tests.hpp"

using namespace ms;

CPPUNIT_TEST_SUITE_REGISTRATION(VectorTest);

void VectorTest::setUp() {
    
}

void VectorTest::tearDown() {

}

void VectorTest::testCopyConstructor() {
    
    math::Vector<float, 3> vec1(2, 2, 2);
    math::Vector<float, 3> vec2(vec1);
    
    CPPUNIT_ASSERT(vec1.c_array() != vec2.c_array());
    
    for (int i = 0; i < 3; ++ i) {
        CPPUNIT_ASSERT(vec1.c_array()[i] == vec2.c_array()[i]);
    }
    
}

void VectorTest::testMoveConstructor() {
    
    math::Vector<float, 3> vec1(2, 2, 2);
    const float* ptrToComponents = vec1.c_array();
    
    math::Vector<float, 3> vec2(std::move(vec1));
    CPPUNIT_ASSERT(vec2.c_array() == ptrToComponents);
    CPPUNIT_ASSERT(vec1.c_array() == nullptr);

}

void VectorTest::testMoveAssignment() {
    
    math::Vector<float, 3> vec1(2, 2, 2);
    math::Vector<float, 3> vec2;
    
    const float* ptrToComponents = vec1.c_array();
    
    vec2 = std::move(vec1);
    
    CPPUNIT_ASSERT(vec2.c_array() == ptrToComponents);
    CPPUNIT_ASSERT(vec1.c_array() == nullptr);
    
}

void VectorTest::testCopyAssignment() {
    
    math::Vector<float, 3> vec1(2, 2, 2);
    math::Vector<float, 3> vec2;
    
    const float* ptrToComponents = vec1.c_array();
    
    vec2 = vec1;
    
    CPPUNIT_ASSERT(vec2.c_array() != ptrToComponents);
    CPPUNIT_ASSERT(vec1.c_array() != nullptr);
    
    for (int i = 0; i < 3; ++ i) {
        CPPUNIT_ASSERT(vec1.c_array()[i] == vec2.c_array()[i]);
    }
    
}

void VectorTest::testEquals() {
    
    math::Vector<float, 3> vec1(2, 2, 2);
    math::Vector<float, 3> vec2(2, 2, 2);

    CPPUNIT_ASSERT(vec2 == vec1);
    CPPUNIT_ASSERT(!(vec2 != vec1));
    
    vec2 = math::Vector<float, 3>(3, 3, 3);
    CPPUNIT_ASSERT(vec2 != vec1);
    CPPUNIT_ASSERT(!(vec2 == vec1));
    
}

void VectorTest::testLength() {
    
    math::Vector<float, 4> vec1(3, 3, 3, 3);
    
    CPPUNIT_ASSERT(vec1.length() == 6);
    
}

void VectorTest::testAddition() {
    
    math::Vector<float, 3> vec1(2, 2, 2);
    math::Vector<float, 3> vec2(2, 2 ,2);
    
    math::Vector<float, 3> vec3;
    
    vec3 = vec1 + vec2;
    
    for (int i = 0; i < 3; ++ i) {
        CPPUNIT_ASSERT(vec3.c_array()[i] == 4);
    }
    
    vec3 += vec1;
    
    for (int i = 0; i < 3; ++ i) {
        CPPUNIT_ASSERT(vec3.c_array()[i] == 6);
    }
    
}

void VectorTest::testSubtraction() {
   
    math::Vector<float, 3> vec1(2, 2, 2);
    math::Vector<float, 3> vec2(2, 2, 2);
    
    math::Vector<float, 3> vec3;
    
    vec3 = vec1 - vec2;
    
    for (int i = 0; i < 3; ++ i) {
        CPPUNIT_ASSERT(vec3.c_array()[i] == 0);
    }
    
    vec3 -= vec1;
    
    for (int i = 0; i < 3; ++ i) {
        CPPUNIT_ASSERT(vec3.c_array()[i] == -2);
    }
    
}

void VectorTest::testComponentsAccess() {
    
    constexpr int dim = 4;
    
    math::Vector<float, dim> vec1(2, 2, 2, 2);
    for (int i = 0; i < dim; ++ i) {
        CPPUNIT_ASSERT(vec1[i] == 2);
        vec1[i] = i;
    }
    
    for (int i = 0; i < dim; ++ i) {
        CPPUNIT_ASSERT(vec1[i] == i);
    }
    
}

void VectorTest::testScalarMultiplication() {
    
    math::Vector<float, 3> vec1(2, 2, 2);
    math::Vector<float, 3> vec3;
    
    vec3 = vec1 * 2;
    
    for (int i = 0; i < 3; ++ i) {
        CPPUNIT_ASSERT(vec3.c_array()[i] == 4);
    }
    
    vec3 = 3.0f * vec1;

    for (int i = 0; i < 3; ++ i) {
        CPPUNIT_ASSERT(vec3.c_array()[i] == 6);
    }
    
    vec3 = operator*(2.0f, vec1);
    
    for (int i = 0; i < 3; ++ i) {
        CPPUNIT_ASSERT(vec3.c_array()[i] == 4);
    }
    
    vec3 *= 2;
    
    for (int i = 0; i < 3; ++ i) {
        CPPUNIT_ASSERT(vec3.c_array()[i] == 8);
    }
    
}

void VectorTest::testDimensionChange() {
	math::vec2 vec1 (2, 3);
	math::vec3 vec2 = vec1.expanded(5);
	
	CPPUNIT_ASSERT(vec2[0] == 2);
	CPPUNIT_ASSERT(vec2[1] == 3);
	CPPUNIT_ASSERT(vec2[2] == 5);

}

void VectorTest::testDot() {
	
	float tab1 [] = { 1.0f, 0.0f, 0.0f };
	float tab2 [] = { 0.0f, 1.0f, 0.0f };
	
	math::Vector<float, 3> vec1(tab1);
	math::Vector<float, 3> vec2(tab2);
	
	CPPUNIT_ASSERT(vec2.dot(vec1) == 0);
	
}

void VectorTest::testCross() {
	
	float tab1 [] = { 1.0f, 2.0f, 3.0f };
	float tab2 [] = { 4.0f, 5.0f, 6.0f };
	
	math::Vector<float, 3> vec1(tab1);
	math::Vector<float, 3> vec2(tab2);
	
	math::Vector<float, 3> result;
	result = vec1.cross(vec2);
	
	CPPUNIT_ASSERT(vec2.dot(vec1) != 0);
	
	CPPUNIT_ASSERT(result[0] == -3);
	CPPUNIT_ASSERT(result[1] == 6);
	CPPUNIT_ASSERT(result[2] == -3);

	
}

void VectorTest::testNormalization() {
	
	float tab2 [] = { 1.0f, 1.0f, 1.0f };
	
	math::Vector<float, 3> vec1(tab2);
	
	CPPUNIT_ASSERT(vec1.length() != 1);
	
	vec1.normalize();
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1, vec1.length(), 0.0001);
	
}

void VectorTest::testMatrixMult() {
	
	float tab2 [] = { 1.0f, 1.0f, 1.0f };
	
	math::Vector<float, 3> vec1(tab2);
	math::Vector<float, 3> vec2(tab2);
	math::mat3 mat = math::mat3::identity();
	
	auto result = vec1 * mat;
	
	CPPUNIT_ASSERT(result == vec1);
	
	math::mat3 mat2 = math::mat3::identity() * 2;

	CPPUNIT_ASSERT(vec1 * 2 == vec1 * mat2);
	CPPUNIT_ASSERT(vec1 * 2 ==  mat2 * vec1);
	
	vec1 *= mat2;
	CPPUNIT_ASSERT(vec1 == vec2 * mat2);
	
}

void VectorTest::testSphericalCoordinatesConversionDegrees() {
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, ms::math::degrees<float>(0), 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(180, ms::math::degrees<float>(M_PI), 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(90, ms::math::degrees<float>(M_PI / 2.0), 0.001);
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, ms::math::radians<float>(0), 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(M_PI / 2.0, ms::math::radians<float>(90), 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(M_PI, ms::math::radians<float>(180), 0.001);
	
	math::spco::DegreesSpherical<float> co;
	math::Vector<float, 3> vec1;
	
	co.radius = 5.0f;
	co.azimuthAngle = 60.0f;
	co.inclination = 30.0f;

	vec1 = math::Vector<float, 3>(co);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.25, vec1[0], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(2.165063509, vec1[1], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(4.330127019, vec1[2], 0.001);
	
	
	
	co.radius = 1.0f;
	co.azimuthAngle = 0;
	co.inclination = 0.0f;

	vec1 = math::Vector<float, 3>(co);

	CPPUNIT_ASSERT(vec1[0] == 0);
	CPPUNIT_ASSERT(vec1[1] == 0);
	CPPUNIT_ASSERT(vec1[2] == 1);

	CPPUNIT_ASSERT(vec1.x() == 0);
	CPPUNIT_ASSERT(vec1.y() == 0);
	CPPUNIT_ASSERT(vec1.z() == 1);
	
	co = math::spco::DegreesSpherical<float>(vec1);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(1, co.radius, 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, co.azimuthAngle, 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, co.inclination, 0.001);

	vec1[0] = 3.0f;
	vec1[1] = 0.0f;
	vec1[2] = 0.0f;

	co = math::spco::DegreesSpherical<float>(vec1);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(3, co.radius, 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, co.azimuthAngle, 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(90, co.inclination, 0.001);
	
	math::spco::RadiansSpherical<float> co2(co);
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL(3, co2.radius, 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, co2.azimuthAngle, 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(M_PI / 2, co2.inclination, 0.001);
	
}

void VectorTest::testSphericalCoordinatesConversionRadians() {
	
	math::spco::RadiansSpherical<float> co;
	
	co.radius = 5.0f;
	co.azimuthAngle = M_PI / 3;
	co.inclination = M_PI / 6;

	math::Vector<float, 3> vec1(co);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.25, vec1[0], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(2.165063509, vec1[1], 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(4.330127019, vec1[2], 0.001);

	co.radius = 1.0f;
	co.azimuthAngle = 0;
	co.inclination = 0.0f;
	
	vec1 = math::Vector<float, 3>(co);
	
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1, co.radius, 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, co.azimuthAngle, 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, co.inclination, 0.001);

	vec1[0] = 3.0f;
	vec1[1] = 0.0f;
	vec1[2] = 0.0f;

	co = math::spco::RadiansSpherical<float>(vec1);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(3, co.radius, 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, co.azimuthAngle, 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(M_PI / 2, co.inclination, 0.001);
	
	math::spco::DegreesSpherical<float> co2(co);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(3, co2.radius, 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, co2.azimuthAngle, 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(90, co2.inclination, 0.001);
	
}


