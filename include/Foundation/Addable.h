/*
 *  Addable.h
 *  XQL
 *
 *  Created by Izaak Schroeder on 09-12-01.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

namespace I {
	template<class T> class Addable 
	{
	public:
		virtual T operator + (const T&) = 0;
	};
};
