#include "frustum_tests.hpp"

using namespace ms;
using namespace math;

CPPUNIT_TEST_SUITE_REGISTRATION( FrustumTest );

void FrustumTest::setUp() {
    
}

void FrustumTest::tearDown() {

}

void FrustumTest::frustumInitialization() {

	FrustumViewport<float> f{0.01f, 100.0f, 90.0f, 16.0f/9.0f};
	OrthographicViewport<float> o{1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f};
	
	BoundingBox<float> b{-0.5f, 0.5f, -0.5f, 0.5f, -0.5f, 0.5f};
	
	CPPUNIT_ASSERT(!f.is_in_camera_sight(translate<float, 4>(vec3{0.0f, 0.0f, 200.0f}), b));
	CPPUNIT_ASSERT(!f.is_in_camera_sight(translate<float, 4>(vec3{0.0f, 0.0f, 120.0f}), b));
	CPPUNIT_ASSERT(f.is_in_camera_sight(mat4::identity(), b));
	
	CPPUNIT_ASSERT(o.is_in_camera_sight(mat4::identity(), b));
	CPPUNIT_ASSERT(!o.is_in_camera_sight(translate<float, 4>(vec3{0.0f, 100.0f, 0.0f}), b));
	CPPUNIT_ASSERT(!o.is_in_camera_sight(translate<float, 4>(vec3{0.0f, 100.0f, 0.0f}), b));
	
}

void FrustumTest::measureTestingPerformance() {
	
	FrustumViewport<float> f{0.01f, 100.0f, 90.0f, 16.0f/9.0f};
	BoundingBox<float> b{-0.5f, 0.5f, -0.5f, 0.5f, -0.5f, 0.5f};
	
	
	unsigned int testsAmount = 1000000;
	float maxNumber = 330.0f;
	
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	
	auto frustumCullingTime = measure_time<std::chrono::milliseconds>([&](){
		
		auto transformationMatrix = transform::translate<float, 4>(vec3{std::rand()/maxNumber, std::rand()/maxNumber, std::rand()/maxNumber});
		
		for(long i = 0; i < testsAmount; ++i) {
			
			f.is_in_camera_sight(transformationMatrix, b);
			
		}
		
	});
	
	std::cout << std::endl;
	std::cout << "is_in_camera_sight:" << frustumCullingTime << std::endl;
	std::cout << std::endl;
}

void FrustumTest::measureInitializationPerformance() {
	
	unsigned int testsAmount = 1000000;
	float maxNumber = 330.0f;
	
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	
	auto initializationTime = measure_time<std::chrono::milliseconds>([&](){
		
		
		
		for(long i = 0; i < testsAmount; ++i) {
			
			FrustumViewport<float> b{std::rand()/maxNumber, std::rand()/maxNumber, std::rand()/maxNumber, std::rand()/maxNumber};

		}
		
	});
	
	std::cout << std::endl;
	std::cout << "initialization:" << initializationTime << std::endl;
	std::cout << std::endl;
}
