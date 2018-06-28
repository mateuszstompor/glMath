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

namespace ms {
    
    namespace math {
        
        template <typename Type>
        class FrustumViewport {
            
            template <typename T, UNSIGNED_TYPE Dimension>
            friend class Vector;
            
            template <typename T>
            friend class Plane;
            
            using vec3T = Vector<Type, 3>;
            
        public:
            
            FrustumViewport 		(Type nearPlane,
                                     Type farPlane,
                                     Type fovDegrees,
                                     Type aspectRatio);
            
            bool 								is_in_camera_sight 		(mat4 const & boundingBoxTransformation,
                                                                         BoundingBox<Type> const & boundingBox) const;
            
            constexpr 	math::mat4 const & 					get_projection_matrix   () const;
            
        private:
            
            mat4 const 										projectionMatrix;
            BoxPlanes<Type>									boxPlanes;
            
        };
        
    }
    
}
template<typename Type>
ms::math::FrustumViewport<Type>::FrustumViewport (Type nearPlane,
                                                  Type farPlane,
                                                  Type fovDegrees,
                                                  Type aspectRatio) : projectionMatrix(std::move(projection::perspective(nearPlane, farPlane, fovDegrees, aspectRatio))) {
    
    
    auto right = vec3T{Type{1.0}, Type{0.0}, Type{0.0}};
    auto up = vec3T{Type{0.0}, Type{1.0}, Type{0.0}};
    
    auto nearPlaneOrigin = vec3{Type{0.0}, Type{0.0}, nearPlane};
    auto farPlaneOrigin = vec3{Type{0.0}, Type{0.0}, farPlane};
    
    float nearPlaneHalfWidth 	= nearPlane * tan(math::radians(fovDegrees));
    float nearPlaneHalfHeight 	= nearPlaneHalfWidth / aspectRatio;
    float farPlaneHalfWidth 	= farPlane * tan(math::radians(fovDegrees));
    float farPlaneHalfHeight 	= farPlaneHalfWidth / aspectRatio;
    
    vec3T c {nearPlaneOrigin - right * nearPlaneHalfWidth - up * nearPlaneHalfHeight};
    vec3T d {nearPlaneOrigin + right * nearPlaneHalfWidth - up * nearPlaneHalfHeight};
    vec3T a {nearPlaneOrigin - right * nearPlaneHalfWidth + up * nearPlaneHalfHeight};
    vec3T b {nearPlaneOrigin + right * nearPlaneHalfWidth + up * nearPlaneHalfHeight};
    
    vec3T e {farPlaneOrigin - right * farPlaneHalfWidth + up * farPlaneHalfHeight};
    vec3T f {farPlaneOrigin + right * farPlaneHalfWidth + up * farPlaneHalfHeight};
    vec3T g {farPlaneOrigin - right * farPlaneHalfWidth - up * farPlaneHalfHeight};
    vec3T h {farPlaneOrigin + right * farPlaneHalfWidth - up * farPlaneHalfHeight};
    
    boxPlanes.front 	= math::Plane<float>::from_points(c, a, b);
    boxPlanes.back 		= math::Plane<float>::from_points(g, e, f);
    boxPlanes.top  		= math::Plane<float>::from_points(e, f, b);
    boxPlanes.bottom 	= math::Plane<float>::from_points(d, h, g);
    boxPlanes.left 		= math::Plane<float>::from_points(e, a, c);
    boxPlanes.right 	= math::Plane<float>::from_points(f, h, d);
    
}

template<typename Type>
bool ms::math::FrustumViewport<Type>::is_in_camera_sight (mat4 const & boundingBoxTransformation,
                                                          BoundingBox<Type> const & boundingBox) const {
    
    if(boxPlanes.left.get_position(boundingBoxTransformation, boundingBox) == math::Plane<float>::RelativePosition::in_front)
        return false;
    
    if(boxPlanes.right.get_position(boundingBoxTransformation, boundingBox) == math::Plane<float>::RelativePosition::in_front)
        return false;
    
    if(boxPlanes.front.get_position(boundingBoxTransformation, boundingBox) == math::Plane<float>::RelativePosition::in_front)
        return false;
    
    if(boxPlanes.top.get_position(boundingBoxTransformation, boundingBox) == math::Plane<float>::RelativePosition::in_front)
        return false;
    
    if(boxPlanes.back.get_position(boundingBoxTransformation, boundingBox) == math::Plane<float>::RelativePosition::in_front)
        return false;
    
    if(boxPlanes.bottom.get_position(boundingBoxTransformation, boundingBox) == math::Plane<float>::RelativePosition::in_front)
        return false;
    
    return true;
    
}

template<typename Type>
constexpr ms::math::mat4 const & ms::math::FrustumViewport<Type>::get_projection_matrix () const {
    return projectionMatrix;
}
