/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include <exception>
#include <typeinfo>

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
                 // needs a workaround thanks to  wtravisjones for bug report.
    #define INFECTORPP_NOEXCEPT noexcept(true)
#else
    #define INFECTORPP_NOEXCEPT
#endif

namespace Infector{
namespace priv{
	
	void logCriticalError(const char * message);

	template< typename M>
	void throwOrBreak(){
		
		logCriticalError(typeid(M).name());
		#ifdef INFECTORPP_DISABLE_EXCEPTION_HANDLING
			assert( false);
		#else
			throw M();
		#endif
	}
	
	template< typename M>
	void throwingAssertion( bool condition){
		if( condition == false)
			throwOrBreak< M>();
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
			return "\nThis is for sure a bug, please report it at: \n"
					"https://github.com/Darelbi/Infectorpp \n"
					"Make sure to provide code that reproduce the problem";
        }
    };
	
	class PartiallyImplementedSharedType: public std::exception{
	public:
		virtual const char * what() const INFECTORPP_NOEXCEPT{
			return "In container you binded a Concrete type as multiple \n"
					"interfaces, but then you registered an instance for only\n"
					"a bunch of those interfaces: if you got this exception\n"
					"is because somewhere on your code it was assumed\n"
					"those interfaces are still communicating each other\n"
					"See the wiki for fixing this exception";
			
		}
	};
	
	class TypeNotWiredEx: public std::exception{
	public:
		virtual const char* what() const INFECTORPP_NOEXCEPT{
			return "\nYou trying to build instance or component of a type wich was not wired.\n";
        }
    };
		
	class InstanceAlreadyRegisteredEx: public std::exception{
	public:
		virtual const char* what() const INFECTORPP_NOEXCEPT{
			return "\nCannot register an instance that was already lazily created..\n";
        }
    };
	
	class NotBoundEx: public std::exception{
	public:
		virtual const char* what() const INFECTORPP_NOEXCEPT{
			return "\nCannot wire a type without bindings.\n";
        }	
	};
}
}