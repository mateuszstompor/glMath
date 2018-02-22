//
//  matrix.h
//  glMath
//
//  Created by Mateusz Stompór on 22/02/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#ifndef matrix_h
#define matrix_h

#include <string>

#include "common.h"

namespace ms {
	
	namespace math {
	
		template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
		class Matrix {
			
		public:
			
							Matrix				();
			
							Matrix				(Type value);
			
							Matrix				(const Matrix & m);
			
							Matrix				(Matrix && m);
			
							Matrix				(const Type array [Rows * Columns]);
			
			Matrix &		operator =			(const Matrix & m);
		
			Matrix &		operator =			(Matrix && m);
			
			Matrix 			operator - 			(const Matrix & m);
			
			Matrix & 		operator -= 		(const Matrix & m);
			
			Matrix 			operator + 			(const Matrix & m);
			
			Matrix & 		operator += 		(const Matrix & m);
			
			Matrix & 		operator *= 		(const Matrix & m);
			
			Matrix	 		operator *	 		(const Matrix & m);
			
			Matrix & 		operator *= 		(Type value);
			
			Matrix	 		operator *	 		(Type value);
			
			bool	 		operator ==	 		(const Matrix & m);
			
			bool	 		operator !=	 		(const Matrix & m);
			
			Type & 			operator []			(UNSIGNED_TYPE index);
			
			Matrix 			add 				(const Matrix & m);
			
			Matrix 			subtract 			(const Matrix & m);
			
			Type & 			at					(UNSIGNED_TYPE index);
			
			std::string 	to_string			() const;
			
			const Type * 	c_array				() const;
			
		private:
			
			Type * 			components;
			
		};
		
	}
	
}

//TODO
//Matrix				();

//TODO
//Matrix				(Type value);

//TODO
//Matrix				(const Matrix & m);

//TODO
//Matrix				(Matrix && m);

//TODO
//Matrix				(const Type array [Rows * Columns]);

//TODO
//Matrix&			operator =			(const Matrix & m);

//TODO
//Matrix&			operator =			(Matrix && m);

//TODO
//Matrix 			operator - 			(const Matrix & m);

//TODO
//Matrix & 			operator -= 		(const Matrix & m);

//TODO
//Matrix 			operator + 			(const Matrix & m);

//TODO
//Matrix & 			operator += 		(const Matrix & m);

//TODO
//Matrix & 		operator *= 		(const Matrix & m);

//TODO
//Matrix	 		operator *	 		(const Matrix & m);

//TODO
//Matrix & 		operator *= 		(Type value);

//TODO
//Matrix	 		operator *	 		(Type value);

//TODO
//bool	 		operator ==	 		(const Matrix & m);

//TODO
//bool	 		operator !=	 		(const Matrix & m);

//TODO
//Matrix 			add 				(const Matrix & m);

//TODO
//Matrix 			subtract 			(const Matrix & m);

//TODO
//Type & 			operator []			(UNSIGNED_TYPE index);

//TODO
//Type & 			at					(UNSIGNED_TYPE index);

//TODO
//std::string 	to_string			() const;

//TODO
//const Type * 	c_array				() const;

#endif
