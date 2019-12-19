//
//  plane.h
//  glMath
//
//  Created by Mateusz Stompór on 31/03/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#pragma once

#include <utility>

#include "../internal/definitions.h"
#include "../geometry/bounding_box.h"

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
                                    Plane               ();
                                    Plane               (const vec3T & normal,
                                                         const vec3T & origin);
        bool                        is_in_front         (BoundingBox<Type> const & boundingBox) const;
        RelativePosition            get_position        (Matrix<Type, 4, 4> const & m,
                                                         BoundingBox<Type> const & boundingBox) const;
        RelativePosition            get_position        (BoundingBox<Type> const & boundingBox) const;
        constexpr vec3T const &     get_normal          () const;
        constexpr vec3T const &     get_origin          () const;
        constexpr vec4T const &     get_normal4         () const;
        constexpr vec4T const &     get_origin4         () const;
        std::optional<Type>         intersection        (Ray<Type, 3> ray, Type epsilon);
        std::optional<vec3T>        intersection_point  (Ray<Type, 3> ray);
        // Clockwise
        static Plane                from_points         (vec3T const & firstPoint,
                                                         vec3T const & origin,
                                                         vec3T const & secondPoint);
        static Plane                from_points         (vec3T && firstPoint,
                                                         vec3T && origin,
                                                         vec3T && secondPoint);
    private:
        // Duplication speed up calculations a lot
        Vector<Type, 3>  	normal;
        Vector<Type, 4>  	normal4;
        // Origin of normal vector
        Vector<Type, 3>  	originPoint;
        Vector<Type, 4>  	originPoint4;
    };
}

template <typename Type>
ms::math::Plane<Type>::Plane () : normal{}, originPoint{} {}

template <typename Type>
ms::math::Plane<Type>::Plane(const vec3T & n,
                             const vec3T & o) : normal(n), normal4(n, 1.0f), originPoint(o), originPoint4(o, 1.0f) { }

template <typename Type>
bool ms::math::Plane<Type>::is_in_front (BoundingBox<Type> const & boundingBox) const {
    for(int i{0}; i < 8 ; ++i) {
        if((boundingBox.corners[i] - originPoint4).dot_xyz(normal4) < 0)
            return false;
    }
    return true;
}

template <typename Type>
typename ms::math::Plane<Type>::RelativePosition ms::math::Plane<Type>::get_position (const Matrix<Type, 4, 4> & m, const BoundingBox<Type> & boundingBox) const {
    bool inFront{true}, behind{true}, result;
    for(int i{0}; i < 8 && (behind || inFront); ++i) {
        result = ((m * boundingBox.corners[i]) -= originPoint4).dot_xyz(normal4) > 0;
        inFront = inFront && result;
        behind = behind && !result;
    }
    return !(inFront || behind) ? RelativePosition::intersects : (!inFront ? RelativePosition::behind : RelativePosition::in_front);
}

template <typename Type>
typename ms::math::Plane<Type>::RelativePosition ms::math::Plane<Type>::get_position (BoundingBox<Type> const & boundingBox) const {
    bool isInFront{true}, isBehind{true}, result;
    for(int i = 0; i < 8 && (isBehind || isInFront); ++i) {
        result = (boundingBox.corners[i] - originPoint4).dot_xyz(normal4) > 0;
        isInFront = isInFront && result;
        isBehind = isBehind && !result;
    }
    return !isInFront && !isBehind ? RelativePosition::intersects : (!isInFront ? RelativePosition::behind : RelativePosition::in_front);
}

template <typename Type>
constexpr ms::math::Vector<Type, 3> const & ms::math::Plane<Type>::get_normal () const {
    return normal;
}

template <typename Type>
constexpr ms::math::Vector<Type, 3> const & ms::math::Plane<Type>::get_origin () const {
    return originPoint;
}

template <typename Type>
constexpr ms::math::Vector<Type, 4> const & ms::math::Plane<Type>::get_normal4 () const {
    return normal4;
}

template <typename Type>
constexpr ms::math::Vector<Type, 4> const & ms::math::Plane<Type>::get_origin4 () const {
    return originPoint4;
}

template <typename Type>
ms::math::Plane<Type> ms::math::Plane<Type> :: from_points(vec3T const & firstPoint, vec3T const & origin, vec3T const & secondPoint) {
    auto firstVector = firstPoint - origin;
    auto secondVector = secondPoint - origin;
    auto normal = firstVector.cross(secondVector).normalize();
    return ms::math::Plane<Type>(std::move(normal), origin);
}

template <typename Type>
ms::math::Plane<Type> ms::math::Plane<Type>::from_points(vec3T && firstPoint, vec3T && origin, vec3T && secondPoint) {
    firstPoint -= origin;
    secondPoint -= origin;
    auto normal = firstPoint.cross(secondPoint).normalize();
    return ms::math::Plane<Type>(std::move(normal), std::move(origin));
}

template <typename Type>
std::optional<typename ms::math::Vector<Type, 3>> ms::math::Plane<Type>::intersection_point (ms::math::Ray<Type, 3> ray) {
    auto intersection_variable = intersection(ray, std::numeric_limits<Type>::epsilon());
    if (intersection_variable.has_value()) {
        return ray.direction * *intersection_variable;
    }
    return std::nullopt;
}

template <typename Type>
std::optional<Type> ms::math::Plane<Type>::intersection (Ray<Type, 3> ray, Type epsilon) {
    auto ndotrn = ray.direction.dot(normal);
    if (std::abs(ndotrn) < epsilon) {
        // add some epsilon
        return std::nullopt;
    }
    return (ray.origin - originPoint).dot(ray.direction) / ndotrn;
}