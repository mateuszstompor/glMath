//
//  main.cpp
//  glMath
//
//  Created by Mateusz Stompór on 17/12/2019.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#include "ray_tests.hpp"
#include "sphere_tests.h"
#include "plane_tests.hpp"
#include "matrix_tests.hpp"
#include "vector_tests.hpp"
#include "frustum_tests.hpp"
#include "boundingbox_tests.hpp"

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}