/*
 *  TestSuite.h
 *  XQL
 *
 *  Created by Izaak Schroeder on 09-12-02.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _TESTSUITE_H_
#define _TESTSUITE_H_

#define Assert(c) this->_Assert(c, "Failed assertion.", __FILE__ ":" TOSTR2(__LINE__));
#define Trace(c) this->_Trace(c, __FILE__ ":" TOSTR2(__LINE__));

#ifndef export
#ifdef _WIN32 
#define export __declspec(dllexport)
#else
#define export 
#endif
#endif

namespace I
{
	class TestSuite 
	{
	public:
		virtual void Run() = 0;
		export virtual ~TestSuite();
	protected:
		export void _Assert(bool Condition, const char* Message, const char* CodeInfo);
		export void _Trace(const char* Message, const char* CodeInfo);
	};
};


#endif
