//
//  common.h
//  glMath
//
//  Created by Mateusz Stompór on 22/02/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#pragma once

#include <cstdint>
#include <cassert>
#include <iostream>

#ifdef __WIN32__

#define _USE_MATH_DEFINES
#include <math.h>

#else

#include <cmath>

#endif


namespace ms::math {
    #define UNSIGNED_TYPE std::uint8_t
}

namespace ms {
    template <typename Type>
    inline bool equal(Type value, Type actualValue, Type precision) {
        if(actualValue < (value - precision) || actualValue > (value + precision)) {
            return false;
        }
        return true;
    }
    template <typename Type>
    inline void assert_equal(Type value, Type actualValue, Type precision) {
        if(!equal(value, actualValue, precision)) {
            std::cerr << value << " is not equal " << actualValue << '\n';
            assert(false);
        }
    }
    namespace math {
        template <typename Type>
        inline Type degrees(Type radians) {
            return radians * Type{180.0} / M_PI;
        }
        template <typename Type>
        inline Type radians(Type degrees) {
            return M_PI * (degrees / Type{180.0});
        }
        namespace point {
            template <typename Type>
            inline Type middle(Type p0, Type p1) {
                return (p0 + p1)/Type(2);
            }
            template <typename Type>
            inline Type distance(Type p0, Type p1) {
                return abs(p0 - p1);
            }
        }
    }
}
