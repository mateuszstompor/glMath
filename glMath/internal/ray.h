//
//  ray.h
//  glMath
//
//  Created by Mateusz Stompór on 19/12/2019.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#pragma once

#include "vector.h"

namespace ms::math {
    template <typename Type, std::uint8_t Dimension>
    class Ray {
    public:
                                    Ray(Vector <Type, Dimension> const & origin,
                                        Vector <Type, Dimension> const & direction);
        Vector<Type, Dimension>     origin;
        Vector<Type, Dimension>     direction;
    };
}

namespace ms::math {
    template<typename Type, std::uint8_t Dimension>
    Ray<Type, Dimension>::Ray(Vector <Type, Dimension> const & origin, Vector <Type, Dimension> const & direction) : origin(origin), direction(direction) { }
}