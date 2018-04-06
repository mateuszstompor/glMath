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
			
			RelativePosition	get_position	(Matrix<Type, 4, 4> const & m, BoundingBox<Type> const & boundingBox) const;
			RelativePosition	get_position	(BoundingBox<Type> const & boundingBox) const;
			vec3T const &		get_normal		() const;
			vec3T const &		get_origin		() const;
			
			//clockwise
		static Plane from_points(vec3T firstPoint, vec3T origin, vec3T secondPoint);
			
			// I don't know how can I name second point which lies on the plane :/
			// I'll leave it as it is :)
			
			vec3T const &		get_second		() const;
			
		protected:
			
			Vector<Type, 3> 	normal;
			Vector<Type, 4> 	normal4;
			
			//	origin of normal vector	//
			Vector<Type, 3> 	originPoint;
			Vector<Type, 4> 	originPoint4;
			
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
//	assert_equal(Type(1.0), this->normal.length2(), Type(DEBUG_DEFAULT_PRECISION));
//	assert_equal(Type(1.0), (this->secondPoint-this->originPoint).length2(), Type(DEBUG_DEFAULT_PRECISION));
#endif
	normal4 = normal.expanded(Type(1.0));
	originPoint4 = originPoint.expanded(Type(1.0));
}

template <typename Type>
ms::math::Plane<Type>::Plane (vec3T && n,
							  vec3T && o,
							  vec3T && sp) : normal(n), originPoint(o), secondPoint(sp){
#if DEBUG
//	assert_equal(Type(1.0), this->normal.length2(), Type(DEBUG_DEFAULT_PRECISION));
//	assert_equal(Type(1.0), (this->secondPoint-this->originPoint).length2(), Type(DEBUG_DEFAULT_PRECISION));
#endif
	normal4 = this->normal.expanded(Type(1.0));
	originPoint4 = this->originPoint.expanded(Type(1.0));
}


template <typename Type>
bool ms::math::Plane<Type>::is_valid(Type errorMargin) const {
	return equal(Type(0.0), (secondPoint-originPoint).dot(normal), errorMargin);
}

template <typename Type>
bool ms::math::Plane<Type>::is_in_front (BoundingBox<Type> boundingBox) const {
	for(int i = 0; i < 8; ++i) {
		if((boundingBox.corners[i] - originPoint4).dot(normal4) < 0)
			return false;
	}
	return true;
}

template <typename Type>
typename ms::math::Plane<Type>::RelativePosition ms::math::Plane<Type>::get_position (const Matrix<Type, 4, 4> & m, const BoundingBox<Type> & boundingBox) const {
	bool isInFront = true;
	bool isBehind = true;
	
	bool result = true;
	
	for(int i = 0 ; i < 8 && (isInFront || isBehind); ++i) {
		result = ((m * boundingBox.corners[i]) -= originPoint4).dot(normal4) > 0;
		
		isInFront = isInFront && result;
		isBehind = isBehind && !result;
	}

	return (isInFront || isBehind) == false ? RelativePosition::intersects :
	(isInFront == false ? RelativePosition::behind : RelativePosition::in_front);
}

template <typename Type>
typename ms::math::Plane<Type>::RelativePosition ms::math::Plane<Type>::get_position (BoundingBox<Type> const & boundingBox) const {

	bool isInFront = true;
	bool isBehind = true;
	
	bool result = true;
	
	for(int i = 0; i < 8 && (isInFront || isBehind); ++i) {
		result = (boundingBox.corners[i] - originPoint4).dot(normal4) > 0;
		
		isInFront = isInFront && result;
		isBehind = isBehind && !result;
	}
	
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

template <typename Type>
ms::math::Plane<Type> ms::math::Plane<Type> :: from_points(vec3T firstPoint, vec3T origin, vec3T secondPoint) {
	
	auto firstVector = (firstPoint - origin).normalized();
	auto secondVector = (secondPoint - origin).normalized();
	auto normal = firstVector.cross(secondVector).normalized();
	
	return ms::math::Plane<Type>(normal, origin, origin + secondVector);
}

// I don't know how can I name second point which lies on the plane :/
// I'll leave it as it is :)

template <typename Type>
ms::math::Vector<Type, 3> const & ms::math::Plane<Type>::get_second () const {
	return secondPoint;
}

#endif /* plane_h */
