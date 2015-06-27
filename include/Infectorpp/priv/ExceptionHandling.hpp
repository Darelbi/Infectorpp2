/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include <exception>

//uncomment following line to disable all TRY / CATCH clauses inside Infectorpp

//#define INFECTORPP_DISABLE_EXCEPTION_HANDLING 1

// (you need to recompile Infectorpp)..

// ..Alternatively Cmake GUI has the checkbox option for that

#ifdef INFECTORPP_DISABLE_EXCEPTION_HANDLING
	#undef NDEBUG
	#include <assert.h>

	#undef INFECTORPP_TRY
	#define INFECTORPP_TRY

#else

	#undef INFECTORPP_TRY
	#define INFECTORPP_TRY	try{

#endif

#ifndef _MSC_VER // Visual studio 2013 still does not support "noexcept"
                 // need a workaround thanks to  wtravisjones for bug report.
    #define INFECTORPP_NOEXCEPT noexcept(true)
#else
    #define INFECTORPP_NOEXCEPT
#endif

namespace Infector{
namespace priv{

	template< typename M>
	void throwOrBreak(){
		#ifdef INFECTORPP_DISABLE_EXCEPTION_HANDLING
			assert( false && typeid(M).name());
		#else
			throw M();
		#endif
	}
	
	template< typename M>
	void throwingAssertion( bool condition){
		if(condition==false){
			#ifdef INFECTORPP_DISABLE_EXCEPTION_HANDLING
				assert( condition && typeid(M).name());
			#else
				throw M();
			#endif
		}
	}
	
	class InstantiatingComponentEx: public std::exception{
	public:
        virtual const char* what() const INFECTORPP_NOEXCEPT{
			return 
	"\nCannot create shared instance for something bound as 'unique_ptr'\n";
        }
	};

	class RebindEx: public std::exception{
    public:
        virtual const char* what() const INFECTORPP_NOEXCEPT{
			return "\nCannot bind same interface twice\n";
        }
    };

	class CircularDependencyEx: public std::exception{
    public:
        virtual const char* what() const INFECTORPP_NOEXCEPT{
			return "\nCircular Dependency detected\n";
        }
    };
	
	class TooDeepRecursionEx: public std::exception{
    public:
        virtual const char* what() const INFECTORPP_NOEXCEPT{
			return "\nReached hard recursion limit\n";
        }
    };
	
	class NotReachableEx: public std::exception{
    public:
        virtual const char* what() const INFECTORPP_NOEXCEPT{
			return "\nThis is a infectorpp bug, report it at\n https://github.com/Darelbi/Infectorpp \n";
        }
    };
}
}