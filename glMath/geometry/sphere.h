//
// Created by Mateusz Stompór on 19/12/2019.
//

#pragma once

#include <vector>
#include "../internal/vector.h"

namespace ms::math {
    template<typename T=float>
    class Sphere {
    public:
                                    Sphere                      (Vector<T, 3> const & center, T radius);
        std::vector<T>              intersection_distances      (Ray<T, 3> const & ray);
        std::vector<Vector<T, 3>>   intersection_points         (Ray<T, 3> const & ray);
        Vector<T, 3>                center;
        T                           radius;
    };
}

template<typename T>
ms::math::Sphere<T>::Sphere(Vector<T, 3> const & center, T radius) : center{center}, radius{radius} { }

template<typename T>
std::vector<T> ms::math::Sphere<T>::intersection_distances (Ray<T, 3> const & ray) {
    std::vector<T> result{};
    Vector<T, 3> oc = ray.origin - center;
    T a {ray.direction.length2()};
    T b {2 * oc.dot(ray.direction)};
    T c {oc.length2() - radius * radius};
    T discriminant = b*b - T{4} * a * c;
    if (discriminant >= 0) {
        T denominant {T{2} * a};
        T delta (sqrt(b * b - 4.0 * a * c));
        T first = (-b - delta)/denominant;
        T second = (-b + delta)/denominant;
        result.push_back(first);
        if (first!=second)
            result.push_back(second);
    }
    return result;
}

template<typename T>
std::vector<ms::math::Vector<T, 3>> ms::math::Sphere<T>::intersection_points (Ray<T, 3> const & ray) {
    std::vector<ms::math::Vector<T, 3>> result {};
    for(auto distance : intersection_distances(ray))
        result.push_back(ray.origin + ray.direction * distance);
    return result;
}