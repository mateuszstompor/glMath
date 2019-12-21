//
//  frustum_viewport.h
//  glMath
//
//  Created by Mateusz Stompór on 17/04/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#pragma once

#include "plane.h"
#include "box.h"

//
//               e-------f
//              /|      /|
//             / |     / |
//            a--|----b  |
//            |  g----|--h
//            | /     | /
//            c-------d
//
//                 ^
//                 |       direction of sight
//               camera
//
//
// points {c, d, g, h} - plane bottom
// points {a, b, e, f} - plane top
// points {c, g, a, e} - plane left
// points {d, b, h, f} - plane right
// points {a, b, c, d} - plane front
// points {g, e, f, h} - plane back

namespace ms::math {
    template <typename Type>
    class FrustumViewport {
        template <typename T, std::uint8_t Dimension>
        friend class Vector;
        template <typename T>
        friend class Plane;
        using vec3T = Vector<Type, 3>;
    public:

                                                        FrustumViewport         (Type nearPlane,
                                                                                 Type farPlane,
                                                                                 Type fovDegrees,
                                                                                 Type aspectRatio);
        bool                                            is_in_camera_sight      (mat4 const & boundingBoxTransformation,
                                                                                 BoundingBox<Type> const & boundingBox) const;
        [[nodiscard]] constexpr math::mat4 const &      get_projection_matrix   () const;
    private:
        mat4 const                                      projection_matrix;
        BoxPlanes<Type>                                 box_planes;
    };
}
template<typename Type>
ms::math::FrustumViewport<Type>::FrustumViewport (Type nearPlane,
                                                  Type farPlane,
                                                  Type fovDegrees,
                                                  Type aspectRatio) : projection_matrix(std::move(projection::perspective(nearPlane, farPlane, fovDegrees, aspectRatio))) {
    auto right = vec3T{Type{1.0}, Type{0.0}, Type{0.0}};
    auto up = vec3T{Type{0.0}, Type{1.0}, Type{0.0}};
    auto near_plane_origin = vec3{Type{0.0}, Type{0.0}, nearPlane};
    auto far_plane_origin = vec3{Type{0.0}, Type{0.0}, farPlane};
    Type near_plane_half_width     = nearPlane * tan(math::radians(fovDegrees));
    Type near_plane_half_height    = near_plane_half_width / aspectRatio;
    Type far_plane_half_width      = farPlane * tan(math::radians(fovDegrees));
    Type far_plane_half_height     = far_plane_half_width / aspectRatio;
    vec3T c {near_plane_origin - right * near_plane_half_width - up * near_plane_half_height};
    vec3T d {near_plane_origin + right * near_plane_half_width - up * near_plane_half_height};
    vec3T a {near_plane_origin - right * near_plane_half_width + up * near_plane_half_height};
    vec3T b {near_plane_origin + right * near_plane_half_width + up * near_plane_half_height};
    vec3T e {far_plane_origin - right * far_plane_half_width + up * far_plane_half_height};
    vec3T f {far_plane_origin + right * far_plane_half_width + up * far_plane_half_height};
    vec3T g {far_plane_origin - right * far_plane_half_width - up * far_plane_half_height};
    vec3T h {far_plane_origin + right * far_plane_half_width - up * far_plane_half_height};
    box_planes.front        = math::Plane<Type>::from_points(c, a, b);
    box_planes.back         = math::Plane<Type>::from_points(g, e, f);
    box_planes.top          = math::Plane<Type>::from_points(e, f, b);
    box_planes.bottom       = math::Plane<Type>::from_points(d, h, g);
    box_planes.left         = math::Plane<Type>::from_points(e, a, c);
    box_planes.right        = math::Plane<Type>::from_points(f, h, d);
}

template<typename Type>
bool ms::math::FrustumViewport<Type>::is_in_camera_sight (mat4 const & boundingBoxTransformation,
                                                          BoundingBox<Type> const & boundingBox) const {
    if(box_planes.left.get_position(boundingBoxTransformation, boundingBox) == math::Plane<Type>::RelativePosition::in_front)
        return false;
    if(box_planes.right.get_position(boundingBoxTransformation, boundingBox) == math::Plane<Type>::RelativePosition::in_front)
        return false;
    if(box_planes.front.get_position(boundingBoxTransformation, boundingBox) == math::Plane<Type>::RelativePosition::in_front)
        return false;
    if(box_planes.top.get_position(boundingBoxTransformation, boundingBox) == math::Plane<Type>::RelativePosition::in_front)
        return false;
    if(box_planes.back.get_position(boundingBoxTransformation, boundingBox) == math::Plane<Type>::RelativePosition::in_front)
        return false;
    if(box_planes.bottom.get_position(boundingBoxTransformation, boundingBox) == math::Plane<Type>::RelativePosition::in_front)
        return false;
    return true;
}

template<typename Type>
constexpr ms::math::mat4 const & ms::math::FrustumViewport<Type>::get_projection_matrix () const {
    return projection_matrix;
}
