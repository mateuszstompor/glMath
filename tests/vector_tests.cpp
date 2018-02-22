#include "vector_tests.hpp"

using namespace ms;

CPPUNIT_TEST_SUITE_REGISTRATION(VectorTest);

void VectorTest::setUp() {
    
}

void VectorTest::tearDown() {

}

void VectorTest::testCopyConstructor() {
    
    math::Vector<float, 3> vec1(2);
    math::Vector<float, 3> vec2(vec1);
    
    CPPUNIT_ASSERT(vec1.c_array() != vec2.c_array());
    
    for (int i = 0; i < 3; ++ i) {
        CPPUNIT_ASSERT(vec1.c_array()[i] == vec2.c_array()[i]);
    }
    
}

void VectorTest::testMoveConstructor() {
    
    math::Vector<float, 3> vec1(2);
    const float* ptrToComponents = vec1.c_array();
    
    math::Vector<float, 3> vec2(std::move(vec1));
    CPPUNIT_ASSERT(vec2.c_array() == ptrToComponents);
    CPPUNIT_ASSERT(vec1.c_array() == nullptr);

}

void VectorTest::testMoveAssignment() {
    
    math::Vector<float, 3> vec1(2);
    math::Vector<float, 3> vec2;
    
    const float* ptrToComponents = vec1.c_array();
    
    vec2 = std::move(vec1);
    
    CPPUNIT_ASSERT(vec2.c_array() == ptrToComponents);
    CPPUNIT_ASSERT(vec1.c_array() == nullptr);
    
}

void VectorTest::testCopyAssignment() {
    
    math::Vector<float, 3> vec1(2);
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
    
    math::Vector<float, 3> vec1(2);
    math::Vector<float, 3> vec2(2);

    CPPUNIT_ASSERT(vec2 == vec1);
    CPPUNIT_ASSERT(!(vec2 != vec1));
    
    vec2 = math::Vector<float, 3>(3);
    CPPUNIT_ASSERT(vec2 != vec1);
    CPPUNIT_ASSERT(!(vec2 == vec1));
    
}

void VectorTest::testLength() {
    
    math::Vector<float, 4> vec1(3);
    
    CPPUNIT_ASSERT(vec1.length() == 6);
    CPPUNIT_ASSERT(vec1.precise_length() == 6);
    
}

void VectorTest::testAddition() {
    
    math::Vector<float, 3> vec1(2);
    math::Vector<float, 3> vec2(2);
    
    math::Vector<float, 3> vec3;
    
    vec3 = vec1 + vec2;
    
    for (int i = 0; i < 3; ++ i) {
        CPPUNIT_ASSERT(vec3.c_array()[i] == 4);
    }
    
}

void VectorTest::testSubtraction() {
   
    math::Vector<float, 3> vec1(2);
    math::Vector<float, 3> vec2(2);
    
    math::Vector<float, 3> vec3;
    
    vec3 = vec1 - vec2;
    
    for (int i = 0; i < 3; ++ i) {
        CPPUNIT_ASSERT(vec3.c_array()[i] == 0);
    }
    
}



