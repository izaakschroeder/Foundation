/*
 *  QuickSort.h
 *  XQL
 *
 *  Created by Izaak Schroeder on 09-12-01.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "ComparisonSort.h"

namespace I
{
	template <typename T, template <typename, template <typename> class> class CT, template <typename> class KC = EqualityComparator> class QuickSort : public ComparisonSort<T>
	{
	public:
		void operator () (CT<T,KC>& o)
		{
			if (!o.IsEmpty())
				_Sort(o, 0, o.GetSize()-1);
		}
	protected:
		void _Sort(CT<T,KC>& d, int left, int right)
		{

			int split_pt = Partition(d, left, right);
			if (left < split_pt - 1)
				_Sort(d, left, split_pt-1);
			if (split_pt < right)
				_Sort(d, split_pt, right);
		}
		
		unsigned int Partition(CT<T, KC>& d, int left, int right)
		{
			
			int lm = left;
			int rm = right;
			T val = d[(left+right)/2];
			
			while(lm <= rm)
			{
				while( d[lm] < val)
					++lm;

				while (d[rm] > val)
					--rm;
				
				
					
				if(lm <= rm) 
				{
					T tmp1 = d[lm];
					T tmp2 = d[rm];
					d[lm] = tmp2;
					d[rm] = tmp1;
					++lm;
					--rm;
				}
			}
			return lm;
		}
	};
};