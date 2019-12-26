//
//  plane.h
//  glMath
//
//  Created by Mateusz Stompór on 31/03/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#pragma once

#include <utility>
#include <optional>

#include "bounding_box.h"
#include "../internal/definitions.h"
#include "geometry/triangle/surface_normal.h"

namespace ms::math {
    template <typename Type>
    class Plane {
    protected:
        typedef Vector<Type, 3> vec3T;
        typedef Vector<Type, 4> vec4T;
    public:
        enum class RelativePosition {
            in_front,
            intersects,
            behind
        };
                                    Plane                   ();
                                    Plane                   (const vec3T & normal,
                                                             const vec3T & origin);
        bool                        is_in_front             (BoundingBox<Type> const & bounding_box) const;
        RelativePosition            get_position            (Matrix<Type, 4, 4> const & matrix,
                                                             BoundingBox<Type> const & bounding_box) const;
        RelativePosition            get_position            (BoundingBox<Type> const & bounding_box) const;
        constexpr vec3T const &     get_normal              () const;
        constexpr vec3T const &     get_origin              () const;
        constexpr vec4T const &     get_normal4             () const;
        constexpr vec4T const &     get_origin4             () const;
        std::optional<Type>         intersection_distance   (Ray<Type, 3> ray);
        std::optional<vec3T>        intersection_point      (Ray<Type, 3> ray);
        // Clockwise
        static Plane                from_points             (vec3T const & first_point,
                                                             vec3T const & origin,
                                                             vec3T const & second_point);
        static Plane                from_points             (vec3T && first_point,
                                                             vec3T && origin,
                                                             vec3T && second_point);
    private:
        // Duplication speed up calculations a lot
        Vector<Type, 3>  	normal;
        Vector<Type, 4>  	normal4;
        // Origin of normal vector
        Vector<Type, 3>  	origin;
        Vector<Type, 4>  	origin4;
    };
}

template <typename Type>
ms::math::Plane<Type>::Plane () : normal{}, origin{} {}

template <typename Type>
ms::math::Plane<Type>::Plane(const vec3T & normal,
                             const vec3T & origin) : normal(normal), normal4(normal, 1.0f), origin(origin), origin4(origin, 1.0f) { }

template <typename Type>
bool ms::math::Plane<Type>::is_in_front (BoundingBox<Type> const & bounding_box) const {
    return !std::any_of(bounding_box.corners.begin(), bounding_box.corners.begin() + 8, [&](vec4T vec){
        return (vec - origin4).dot_xyz(normal4) < 0;
    });
}

template <typename Type>
typename ms::math::Plane<Type>::RelativePosition ms::math::Plane<Type>::get_position (const Matrix<Type, 4, 4> & m, const BoundingBox<Type> & bounding_box) const {
    bool in_front{true}, behind{true}, result;
    for(auto i{0}; i < 8 && (behind || in_front); ++i) {
        result = ((m * bounding_box.corners[i]) -= origin4).dot_xyz(normal4) > 0;
        in_front = in_front && result;
        behind = behind && !result;
    }
    return !(in_front || behind) ? RelativePosition::intersects : (!in_front ? RelativePosition::behind : RelativePosition::in_front);
}

template <typename Type>
typename ms::math::Plane<Type>::RelativePosition ms::math::Plane<Type>::get_position (BoundingBox<Type> const & bounding_box) const {
    bool in_front{true}, behind{true}, result;
    for(auto i = 0; i < 8 && (behind || in_front); ++i) {
        result = (bounding_box.corners[i] - origin4).dot_xyz(normal4) > 0;
        in_front = in_front && result;
        behind = behind && !result;
    }
    return !in_front && !behind ? RelativePosition::intersects : (!in_front ? RelativePosition::behind : RelativePosition::in_front);
}

template <typename Type>
constexpr ms::math::Vector<Type, 3> const & ms::math::Plane<Type>::get_normal () const {
    return normal;
}

template <typename Type>
constexpr ms::math::Vector<Type, 3> const & ms::math::Plane<Type>::get_origin () const {
    return origin;
}

template <typename Type>
constexpr ms::math::Vector<Type, 4> const & ms::math::Plane<Type>::get_normal4 () const {
    return normal4;
}

template <typename Type>
constexpr ms::math::Vector<Type, 4> const & ms::math::Plane<Type>::get_origin4 () const {
    return origin4;
}

template <typename Type>
ms::math::Plane<Type> ms::math::Plane<Type>::from_points(vec3T const & first_point, vec3T const & origin, vec3T const & second_point) {
    auto first = first_point - origin;
    auto second = second_point - origin;
    auto normal = first.cross(second).normalize();
    return ms::math::Plane<Type>(std::move(normal), origin);
}

template <typename Type>
ms::math::Plane<Type> ms::math::Plane<Type>::from_points(vec3T && first_point, vec3T && origin, vec3T && second_point) {
    first_point -= origin;
    second_point -= origin;
    auto normal = first_point.cross(second_point).normalize();
    return ms::math::Plane<Type>(std::move(normal), std::move(origin));
}

template <typename Type>
std::optional<typename ms::math::Vector<Type, 3>> ms::math::Plane<Type>::intersection_point (ms::math::Ray<Type, 3> ray) {
    auto intersection_variable = intersection_distance(ray);
    if (intersection_variable)
        return ray.origin + ray.direction * *intersection_variable;
    return std::nullopt;
}

template <typename Type>
std::optional<Type> ms::math::Plane<Type>::intersection_distance (Ray<Type, 3> ray) {
    auto dot = ray.direction.dot(normal);
    if (std::abs(dot) < std::numeric_limits<Type>::epsilon())
        return { };
    return (ray.origin - origin).dot(ray.direction) / dot;
}