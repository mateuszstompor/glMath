//
//  vertex_normal.h
//  glMath
//
//  Created by Mateusz Stompór on 26/12/2019.
//  Copyright © 2019 Mateusz Stompór. All rights reserved.
//

#pragma once

#include <array>
#include <optional>

#include "../vertex.h"
#include "internal/ray.h"


namespace ms::math::triangle::vertex {
    template<typename T, std::uint8_t Dimension>
    class Triangle {
    public:
                                                Triangle                (std::array<Vertex<T, Dimension>, 3> vertices);
        std::array<Vertex<T, Dimension>, 3>     vertices;
    };

    template<typename T, std::uint8_t Dimension>
    Triangle<T, Dimension>::Triangle(std::array<Vertex<T, Dimension>, 3> vertices) : vertices{vertices} { }
}
