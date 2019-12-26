//
//  vertex.h
//  glMath
//
//  Created by Mateusz Stompór on 26/12/2019.
//  Copyright © 2019 Mateusz Stompór. All rights reserved.
//

#pragma once

#include "../internal/vector.h"

namespace ms::math {
    template <typename Type, std::uint8_t Dimension>
    struct Vertex {
        Vector<Type, Dimension>     normal;
        Vector<Type, Dimension>     position;
    };
}
