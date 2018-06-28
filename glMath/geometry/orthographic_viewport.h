//
//  orthographic_viewport.h
//  glMath
//
//  Created by Mateusz Stompór on 17/04/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#pragma once

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
        class OrthographicViewport {
            
            template <typename T, UNSIGNED_TYPE Dimension>
            friend class Vector;
            
            template <typename T>
            friend class Plane;
            
            using vec3T = Vector<Type, 3>;
            
        public:
            
            OrthographicViewport 	(Type _far, 	Type _near,
                                     Type _top, 	Type _bottom,
                                     Type _right,	Type _left);
            
            bool 								is_in_camera_sight 		(mat4 const & boundingBoxTransformation,
                                                                         BoundingBox<Type> const & boundingBox) const;
            
            constexpr 	math::mat4 const & 		get_projection_matrix   () const;
            
        private:
            
            mat4 const 							projectionMatrix;
            BoxPlanes<Type>						boxPlanes;
            
        };
        
    }
    
}
template<typename Type>
ms::math::OrthographicViewport<Type>::OrthographicViewport (Type _far, 		Type _near,
                                                            Type _top, 		Type _bottom,
                                                            Type _right,	Type _left) : projectionMatrix(std::move(projection::orthogonal(_far,
                                                                                                                                            _near,
                                                                                                                                            _top,
                                                                                                                                            _bottom,
                                                                                                                                            _left,
                                                                                                                                            _right))) {
    
    vec3T c {_left, _bottom, _near};
    vec3T d {_right, _bottom, _near};
    vec3T a {_left, _top, _near};
    vec3T b {_right, _top, _near};
    vec3T g {_left, _bottom, _far};
    vec3T h {_right, _bottom, _far};
    vec3T e {_left, _top, _far};
    vec3T f {_right, _top, _far};
    
    boxPlanes.front 	= math::Plane<float>::from_points(b, a, c);
    boxPlanes.back 		= math::Plane<float>::from_points(g, e, f);
    boxPlanes.top 		= math::Plane<float>::from_points(b, f, e);
    boxPlanes.bottom 	= math::Plane<float>::from_points(g, h, d);
    boxPlanes.left 		= math::Plane<float>::from_points(c, a, e);
    boxPlanes.right 	= math::Plane<float>::from_points(f, b, d);
    
}

template<typename Type>
bool ms::math::OrthographicViewport<Type>::is_in_camera_sight (mat4 const & boundingBoxTransformation,
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
constexpr ms::math::mat4 const & ms::math::OrthographicViewport<Type>::get_projection_matrix () const {
    return projectionMatrix;
}
