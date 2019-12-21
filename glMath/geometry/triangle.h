//
// Created by Mateusz Stompór on 20/12/2019.
//

#pragma once

#include <array>
#include "../internal/ray.h"

namespace ms::math {
    template<typename T, std::uint8_t Dimension>
    class Triangle {
    public:
                                                Triangle                (std::array<Vector<T, Dimension>, 3> vertices,
                                                                         Vector<T, Dimension> normal);
        std::optional<T>                        intersection_distance   (Ray<T, 3> ray);
        std::optional<Vector<T, Dimension>>     intersection_point      (Ray<T, 3> ray);
        std::array<Vector<T, Dimension>, 3>     vertices;
        Vector<T, Dimension>                    normal;
    };
}

template<typename T, std::uint8_t Dimension>
ms::math::Triangle<T, Dimension>::Triangle(std::array<Vector<T, Dimension>, 3> vertices, Vector<T, Dimension> normal) : vertices(vertices), normal(normal) { }

template<typename T, std::uint8_t Dimension>
std::optional<T> ms::math::Triangle<T, Dimension>::intersection_distance (Ray<T, 3> ray) {
    auto dot = ray.direction.dot(normal);
    if (dot > 0) {
        // Normal of ray and the plane of triangles should point at each other
        return { };
    }
    if (std::abs(dot) < std::numeric_limits<T>::epsilon())
        return { };
    auto distance = (ray.origin - vertices[0]).dot(ray.direction) / dot;
    auto intersection_point = ray.origin + distance * ray.direction;
    // Inside-outside test
    {
        auto edge = vertices[1] - vertices[0];
        auto vp = intersection_point - vertices[0];
        if(normal.dot(edge.cross(vp)) > 0) {
            return std::nullopt;
        }
    }
    {
        auto edge = vertices[2] - vertices[1];
        auto vp = intersection_point - vertices[1];
        if(normal.dot(edge.cross(vp)) > 0) {
            return std::nullopt;
        }
    }
    {
        auto edge = vertices[0] - vertices[2];
        auto vp = intersection_point - vertices[2];
        if(normal.dot(edge.cross(vp)) > 0) {
            return std::nullopt;
        }
    }
    return distance;
}

template<typename T, std::uint8_t Dimension>
std::optional<ms::math::Vector<T, Dimension>> ms::math::Triangle<T, Dimension>::intersection_point(Ray<T, 3> ray) {
    auto intersection_variable = intersection_distance(ray);
    if (intersection_variable)
        return ray.origin + ray.direction * *intersection_variable;
    return std::nullopt;
}
