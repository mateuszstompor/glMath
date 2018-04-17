//
//  helper.h
//  glMath
//
//  Created by Mateusz Stompór on 17/04/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#ifndef helper_h
#define helper_h

#include <chrono>

template<typename T>
inline long measure_time(std::function<void(void)> lambda) {
	auto start = std::chrono::high_resolution_clock::now();
	lambda();
	auto now = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<T>(now - start).count();
}

#endif /* helper_h */
