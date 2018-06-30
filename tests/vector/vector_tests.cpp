#include "vector_tests.hpp"

using namespace ms;
using namespace math;

CPPUNIT_TEST_SUITE_REGISTRATION(VectorTest);

void VectorTest::setUp() { }

void VectorTest::tearDown() { }

void VectorTest::testCopyConstructor() {

    math::Vector<float, 3> vec1(2, 2, 2);
    math::Vector<float, 3> vec2(vec1);

    CPPUNIT_ASSERT(vec1.c_array() != vec2.c_array());

    for (int i = 0; i < 3; ++ i) {
        CPPUNIT_ASSERT(vec1.c_array()[i] == vec2.c_array()[i]);
    }

	math::Vector<float, 4> vec3(2, 2, 2, 2);
	math::Vector<float, 4> vec4(vec3);

	CPPUNIT_ASSERT(vec3.c_array() != vec4.c_array());

	for (int i = 0; i < 4; ++ i) {
		CPPUNIT_ASSERT(vec3.c_array()[i] == vec4.c_array()[i]);
	}

}

void VectorTest::testPerformance() {
	math::Vector<float, 3> vec1(2, 2, 2);
	math::Vector<float, 4> vec3(2, 2, 2, 2);
	math::mat4 m4(1.0f);
	math::mat3 m3(1.0f);

	auto time1 = measure_time<std::chrono::milliseconds>([&](){

		for(long i = 0; i < 10000000; ++i) {
			math::Vector<float, 3> (2, 2, 2);
		}

	});

	std::cout << "vec3 createion:" << time1 << '\n';

	auto time2 = measure_time<std::chrono::milliseconds>([&](){

		for(long i = 0; i < 10000000; ++i) {
			math::Vector<float, 4>(2, 2, 2, 2);
		}

	});

	std::cout << "vec4 createion:" << time2 << '\n';

	auto time3 = measure_time<std::chrono::milliseconds>([&](){

		for(long i = 0; i < 10000000; ++i) {
			vec3.dot(vec3);
		}

	});

	std::cout << "vec4 dot vec4:" << time3 << '\n';

	auto time4 = measure_time<std::chrono::milliseconds>([&](){

		for(long i = 0; i < 10000000; ++i) {
			vec1.dot(vec1);
		}

	});

	std::cout << "vec3 dot vec3:" << time4 << '\n';

	auto time5 = measure_time<std::chrono::milliseconds>([&](){

		for(long i = 0; i < 10000000; ++i) {
			vec1.length();
		}

	});

	std::cout << "vec3 length:" << time5 << '\n';

	auto time6 = measure_time<std::chrono::milliseconds>([&](){

		for(long i = 0; i < 10000000; ++i) {
			vec3.length();
		}

	});

	std::cout << "vec4 length:" << time6 << '\n';

	auto time7 = measure_time<std::chrono::milliseconds>([&](){

		for(long i = 0; i < 10000000; ++i) {
			vec3.normalize();
		}

	});

	std::cout << "vec4 normalize:" << time7 << '\n';

	auto time8 = measure_time<std::chrono::milliseconds>([&](){

		for(long i = 0; i < 10000000; ++i) {
			vec1.normalize();
		}

	});

	std::cout << "vec3 normalize:" << time8 << '\n';

	auto time9 = measure_time<std::chrono::milliseconds>([&](){

		for(long i = 0; i < 10000000; ++i) {
			vec3.normalized();
		}

	});

	std::cout << "vec4 normalized:" << time9 << '\n';

	auto time10 = measure_time<std::chrono::milliseconds>([&](){

		for(long i = 0; i < 10000000; ++i) {
			vec1.normalized();
		}

	});

	std::cout << "vec3 normalized:" << time10 << '\n';

	auto time11 = measure_time<std::chrono::milliseconds>([&](){

		for(long i = 0; i < 10000000; ++i) {
			CPPUNIT_ASSERT(vec1 == vec1);
		}

	});

	std::cout << "vec3 == vec3:" << time11 << '\n';

	auto time12 = measure_time<std::chrono::milliseconds>([&](){

		for(long i = 0; i < 10000000; ++i) {
			CPPUNIT_ASSERT(vec3 == vec3);
		}

	});

	std::cout << "vec4 == vec4:" << time12 << '\n';

	auto time13 = measure_time<std::chrono::milliseconds>([&](){

		for(long i = 0; i < 10000000; ++i) {
			CPPUNIT_ASSERT(vec1 == vec1);
		}

	});

	std::cout << "vec3 != vec3:" << time13 << '\n';

	auto time14 = measure_time<std::chrono::milliseconds>([&](){

		for(long i = 0; i < 10000000; ++i) {
			CPPUNIT_ASSERT(vec3 == vec3);
		}

	});

	std::cout << "vec4 != vec4:" << time14 << '\n';

	auto time15 = measure_time<std::chrono::milliseconds>([&](){

		for(long i = 0; i < 10000000; ++i) {
			vec1 * m3;
		}

	});

	std::cout << "v3 * m3:" << time15 << '\n';

	auto time16 = measure_time<std::chrono::milliseconds>([&](){

		for(long i = 0; i < 10000000; ++i) {
			vec3 * m4;
		}

	});

	std::cout << "v4 * m4:" << time16 << '\n';

}

void VectorTest::testUnaryMinus() {

	math::Vector<float, 2> vec1(2, 2);
	auto vec2 = -vec1;
	CPPUNIT_ASSERT(vec2 != vec1);
	CPPUNIT_ASSERT(vec2[0] ==  - vec1[0]);
	CPPUNIT_ASSERT(vec2[1] ==  - vec1[1]);

	vec3 v3(1, 2, 3);
	auto v4 = -v3;
	CPPUNIT_ASSERT(v4[0] ==  - v3[0]);
	CPPUNIT_ASSERT(v4[1] ==  - v3[1]);
	CPPUNIT_ASSERT(v4[2] ==  - v3[2]);

	vec4 v5(1, 2, 3, 4);
	auto v6 = -v5;
	CPPUNIT_ASSERT(v5[0] ==  - v6[0]);
	CPPUNIT_ASSERT(v5[1] ==  - v6[1]);
	CPPUNIT_ASSERT(v5[2] ==  - v6[2]);
	CPPUNIT_ASSERT(v5[3] ==  - v6[3]);

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

	for (int i = 0; i < 3; ++ i) {
		CPPUNIT_ASSERT((vec3 + vec3)[i] == 12);
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

	for (int i = 0; i < 3; ++ i) {
		CPPUNIT_ASSERT_DOUBLES_EQUAL((vec3 - vec3)[i], 0, 0.001f);
	}

	for (int i = 0; i < 3; ++ i) {
		CPPUNIT_ASSERT_DOUBLES_EQUAL((vec3 - vec3).components[i], 0, 0.001f);
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
	vec3 *= 2;
	vec3 /= 2;

	vec3 = vec3 / 2;
	vec3 = vec3 * 2;

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

	CPPUNIT_ASSERT(vec3(1, 3, 4).cross(vec3(98, 3, 2)).x() == -6);
	CPPUNIT_ASSERT(vec3(1, 3, 4).cross(vec3(98, 3, 2)).y() == 390);
	CPPUNIT_ASSERT(vec3(1, 3, 4).cross(vec3(98, 3, 2)).z() == -291);

}

void VectorTest::testNormalization() {

	float tab2 [] = { 1.0f, 1.0f, 1.0f };
	float tab3 [] = { 1.0f, 1.0f, 1.0f, 1.0f };

	math::Vector<float, 3> vec1(tab2);
	math::Vector<float, 4> vec2(tab3);

	CPPUNIT_ASSERT(vec1.length() != 1);
	CPPUNIT_ASSERT(vec2.length() != 1);

	vec1.normalize();
	vec2.normalize();

	auto vec3 = (vec1 * 22.0f).normalized();
	auto vec4 = (22.0f * vec2).normalized();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(1, vec1.length(), 0.0001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1, vec2.length(), 0.0001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1, vec3.length(), 0.0001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1, vec4.length(), 0.0001);

}

void VectorTest::testMatrixMult() {

	float tab2 [] = { 1.0f, 1.0f, 1.0f };
	float tab3 [] = { 4.0f, 5.0f, 6.0f };

	math::Vector<float, 3> vec1(tab2);
	math::Vector<float, 3> vec2(tab2);
	math::Vector<float, 3> vec3(tab3);
	math::mat3 mat = math::mat3::identity();

	auto result = vec1 * mat;
	auto result2 = vec3 * mat;

	CPPUNIT_ASSERT(result == vec1);

	math::mat3 mat2 = math::mat3::identity() * 2;

	CPPUNIT_ASSERT(vec1 * 2 == vec1 * mat2);
	CPPUNIT_ASSERT(vec1 * 2 ==  mat2 * vec1);

	vec1 *= mat2;
	CPPUNIT_ASSERT(vec1 == vec2 * mat2);

	CPPUNIT_ASSERT(result2[0] == tab3[0]);
	CPPUNIT_ASSERT(result2[1] == tab3[1]);
	CPPUNIT_ASSERT(result2[2] == tab3[2]);

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

}
