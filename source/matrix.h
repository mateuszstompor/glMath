//
//  matrix.h
//  glMath
//
//  Created by Mateusz Stompór on 22/02/2018.
//  Copyright © 2018 Mateusz Stompór. All rights reserved.
//

#ifndef matrix_h
#define matrix_h

#include "common.h"

namespace ms {
	
	namespace math {
	
		template <typename Type, UNSIGNED_TYPE Rows, UNSIGNED_TYPE Columns>
		class Matrix {
			
		public:
			
							Matrix				();
			
							Matrix				(const Type array [Rows * Columns]);
			
			std::string 	to_string			() const;
			
			const Type * 	c_array				() const;
			
		private:
			
			Type * 			components;
			
		};
		
	}
	
}

#endif
