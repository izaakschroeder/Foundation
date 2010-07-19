/**
 * RopeString.h
 * @author Izaak Schroeder
 */

#ifndef _I_ROPESTRING_H_
#define _I_ROPESTRING_H_

#include <Foundation/Error.h>
#include <Foundation/String.h>

namespace I 
{
	/**
	 * RopeString
	 *
	 *
	 */
	class RopeString<class C> : public String<C>
	{
	public:
		/**
		 * RopeString
		 *
		 *
		 */
		RopeString() : String<C>(), Data(NULL), DataLength(0), TotalLength(0)
		{
			
		}
		
		/**
		 * RopeString
		 *
		 *
		 */
		RopeString(const C* D, unsigned int length, unsigned int offset = 0) : String<C>(), Data(D + offset), DataLength(length - offset), TotalLength(DataLength)
		{
			
		}
		
		/**
		 * RopeString
		 *
		 *
		 */
		RopeString(const RopeString<C>& Other) : String<C>(), Data(Other.Data), DataLength(Other.DataLength), TotalLength(Other.TotalLength)
		{
			
		}
		
		/**
		 * ~RopeString
		 *
		 *
		 */
		virtual ~RopeString()
		{
			
		}
		
		/**
		 * operator + 
		 *
		 *
		 */
		RopeString<C> operator + (const String<C>& Other) const 
		{
			return RopeString<C>(*this, Other);
		}
		
		/**
		 * operator = 
		 *
		 *
		 */
		RopeString<C> operator = (const String<C>& Other) const
		{
			return RopeString<C>(Other);
		}
		
		/**
		 * operator []
		 * @return The ith character in the string
		 */
		C operator [] (unsigned int i) const
		{
			if (i >= TotalLength)
				throw Error();
			if (i < DataLength)
				return Data[i];
			return Right[DataLength - i];
		}
		
		/**
		 * Substring
		 * @return 
		 */
		RopeString<C> Substring(unsigned int Offset, unsigned int Length) const
		{
			if (Offset + Length < DataSize)
				return RopeString<C>(Data, Length, Offset);
			
			
		}
		
		/**
		 * Substring
		 * @return 
		 */
		RopeString<C> Substring(unsigned int Offset) const
		{
			if (Offset >= TotalLength)
				throw Error();
				
			if (Offset < DataLength)
				return RopeString<C>(Data, Offset);
			else
				return Right.Substring(DataLength - Offset);
		}
		
		/**
		 * GetLength
		 * @return The length of the string
		 */
		unsigned int GetLength() const
		{
			return TotalLength;
		}
		
		
	
	private:
		/**
		 * RopeString
		 *
		 *
		 */
		RopeString(const RopeString<C>& L, const RopeString<C>& R) : Data(NULL), DataLength(0), TotalLength(L.TotalLength + R.TotalLength), Left(L), Right(R)
		{
			
		}
		
		const C* Data;
		unsigned int DataLength;
		unsigned int TotalLength;
		const RopeString<C> Left;
		const RopeString<C> Right;
	};
};

#endif
