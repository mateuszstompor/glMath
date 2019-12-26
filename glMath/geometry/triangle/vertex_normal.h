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
        std::optional<T>                        intersection_distance   (Ray<T, 3> ray);
        std::optional<Vector<T, Dimension>>     intersection_point      (Ray<T, 3> ray);
        std::array<Vertex<T, Dimension>, 3>     vertices;
    };

    template<typename T, std::uint8_t Dimension>
    Triangle<T, Dimension>::Triangle(std::array<Vertex<T, Dimension>, 3> vertices) : vertices{vertices} { }

    template<typename T, std::uint8_t Dimension>
    std::optional<T> Triangle<T, Dimension>::intersection_distance (Ray<T, 3> ray) {
        auto first = vertices[0].position - vertices[1].position;
        auto second = vertices[2].position - vertices[1].position;
        auto normal = first.cross(second).normalized();
        auto dot = ray.direction.dot(normal);
        if (dot > 0) {
            // Normal of ray and the plane of triangles should point at each other
            return { };
        }
        if (std::abs(dot) < std::numeric_limits<T>::epsilon())
            return { };
        auto distance = (vertices[0].position-ray.origin).dot(normal)/dot;
        auto intersection_point = ray.origin + distance * ray.direction;
        // Inside-outside test
        {
            auto edge = vertices[1].position - vertices[0].position;
            auto vp = intersection_point - vertices[0].position;
            if(normal.dot(edge.cross(vp)) > 0)
                return std::nullopt;
        }
        {
            auto edge = vertices[2].position - vertices[1].position;
            auto vp = intersection_point - vertices[1].position;
            if(normal.dot(edge.cross(vp)) > 0)
                return std::nullopt;
        }
        {
            auto edge = vertices[0].position - vertices[2].position;
            auto vp = intersection_point - vertices[2].position;
            if(normal.dot(edge.cross(vp)) > 0)
                return std::nullopt;
        }
        return distance;
    }

    template<typename T, std::uint8_t Dimension>
    std::optional<ms::math::Vector<T, Dimension>> Triangle<T, Dimension>::intersection_point(Ray<T, 3> ray) {
        auto intersection_variable = intersection_distance(ray);
        if (intersection_variable)
            return ray.origin + ray.direction * *intersection_variable;
        return std::nullopt;
    }
}
