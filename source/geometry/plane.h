//
//  plane.h
//  glMath
//
//  Created by Mateusz Stompór on 31/03/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#ifndef plane_hpp
#define plane_hpp

#define DEBUG_DEFAULT_PRECISION 0.0001

#include <utility>

#include "../internal/definitions.h"

namespace ms {
	
	namespace math {
		
		template <typename Type>
		class Plane {
			
		protected:
			
			typedef Vector<Type, 3> vec3T;
			
		public:
			
			enum class RelativePosition {
				in_front,
				intersects,
				behind
			};
			
								Plane	(const vec3T & normal,
										 const vec3T & origin,
										 const vec3T & secondPoint);
			
								Plane	(vec3T && normal,
										 vec3T && origin,
										 vec3T && secondPoint);
			
			//																						//
			// checks if vector from origin to second point and normal vector are perpendicular		//
			//																						//
			
			bool 				is_valid		(Type errorMargin = 0.0001f) const;
			
			bool				is_in_front		(BoundingBox<Type> boundingBox) const;
			
			RelativePosition	get_position	(BoundingBox<Type> boundingBox) const;
			
			vec3T const &		get_normal		() const;
			vec3T const &		get_origin		() const;
			
			// I don't know how can I name second point which lies on the plane :/
			// I'll leave it as it is :)
			
			vec3T const &		get_second		() const;
			
		protected:
			
			Vector<Type, 3> 	normal;
			
			//	origin of normal vector	//
			Vector<Type, 3> 	originPoint;
			
			//	second point which is needed (from mathematical point of view) for plane construction	//
			Vector<Type, 3> 	secondPoint;
			
		};
		
	}
	
}

template <typename Type>
ms::math::Plane<Type>::Plane(const vec3T & normal,
							 const vec3T & origin,
							 const vec3T & secondPoint) : normal(normal), originPoint(origin), secondPoint(secondPoint) {
#if DEBUG
	assert_equal(Type(1.0), this->normal.length2(), Type(DEBUG_DEFAULT_PRECISION));
	assert_equal(Type(1.0), (this->secondPoint-this->originPoint).length2(), Type(DEBUG_DEFAULT_PRECISION));
#endif
	
}

template <typename Type>
ms::math::Plane<Type>::Plane (vec3T && normal,
							  vec3T && origin,
							  vec3T && secondPoint) : normal(std::move(normal)), originPoint(std::move(origin)), secondPoint(std::move(secondPoint)){
#if DEBUG
	assert_equal(Type(1.0), this->normal.length2(), Type(DEBUG_DEFAULT_PRECISION));
	assert_equal(Type(1.0), (this->secondPoint-this->originPoint).length2(), Type(DEBUG_DEFAULT_PRECISION));
#endif
	
}


template <typename Type>
bool ms::math::Plane<Type>::is_valid(Type errorMargin) const {
	return equal(Type(0.0), (secondPoint-originPoint).dot(normal), errorMargin);
}

template <typename Type>
bool ms::math::Plane<Type>::is_in_front (BoundingBox<Type> boundingBox) const {
	if((boundingBox.xyz - originPoint).dot(normal) < 0)
		return false;
	if((boundingBox.xyZ - originPoint).dot(normal) < 0)
		return false;
	if((boundingBox.xYz - originPoint).dot(normal) < 0)
		return false;
	if((boundingBox.xYZ - originPoint).dot(normal) < 0)
		return false;
	if((boundingBox.Xyz - originPoint).dot(normal) < 0)
		return false;
	if((boundingBox.XyZ - originPoint).dot(normal) < 0)
		return false;
	if((boundingBox.XYz - originPoint).dot(normal) < 0)
		return false;
	if((boundingBox.XYZ - originPoint).dot(normal) < 0)
		return false;
	return true;
}

template <typename Type>
typename ms::math::Plane<Type>::RelativePosition ms::math::Plane<Type>::get_position (BoundingBox<Type> boundingBox) const {

	bool isInFront = true;
	bool isBehind = true;
	
	bool result = (boundingBox.xyz - originPoint).dot(normal) > 0;
	
	isInFront = isInFront && result;
	isBehind = isBehind && !result;
	
	result = (boundingBox.xyZ - originPoint).dot(normal) > 0;
	
	isInFront = isInFront && result;
	isBehind = isBehind && !result;
	
	result = (boundingBox.xYz - originPoint).dot(normal) > 0;
	
	isInFront = isInFront && result;
	isBehind = isBehind && !result;
	
	result = (boundingBox.xYZ - originPoint).dot(normal) > 0;
	
	isInFront = isInFront && result;
	isBehind = isBehind && !result;
	
	//
	
	result = (boundingBox.Xyz - originPoint).dot(normal) > 0;
	
	isInFront = isInFront && result;
	isBehind = isBehind && !result;
	
	result = (boundingBox.XyZ - originPoint).dot(normal) > 0;
	
	isInFront = isInFront && result;
	isBehind = isBehind && !result;
	
	result = (boundingBox.XYz - originPoint).dot(normal) > 0;
	
	isInFront = isInFront && result;
	isBehind = isBehind && !result;
	
	result = (boundingBox.XYZ - originPoint).dot(normal) > 0;
	
	isInFront = isInFront && result;
	isBehind = isBehind && !result;
	
	return isInFront == false && isBehind == false ? RelativePosition::intersects :
	(isInFront == false ? RelativePosition::behind : RelativePosition::in_front);
}

template <typename Type>
ms::math::Vector<Type, 3> const & ms::math::Plane<Type>::get_normal () const {
	return normal;
}

template <typename Type>
ms::math::Vector<Type, 3> const & ms::math::Plane<Type>::get_origin () const {
	return originPoint;
}

// I don't know how can I name second point which lies on the plane :/
// I'll leave it as it is :)

template <typename Type>
ms::math::Vector<Type, 3> const & ms::math::Plane<Type>::get_second () const {
	return secondPoint;
}

#endif /* plane_h */
