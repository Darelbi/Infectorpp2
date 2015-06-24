/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in InfectorTraits.hpp
*******************************************************************************/
#pragma once
#include <exception>
#include "InfectorAbstractContainer.hpp"

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

#include <iostream>

namespace Infector{
namespace priv{

	template< typename M>
	void throwOrBreak(){
		std::cout<< "throwOrBreak: " <<typeid(M).name()<<std::endl << " " << &typeid(M);
		#ifdef INFECTORPP_DISABLE_EXCEPTION_HANDLING
			std::cout<< "break" <<std::endl;
			assert(false && typeid(M).name());
		#else
			std::cout<< "throw" <<std::endl;
			throw M();
		#endif
	}

	class INFECTORPP_API RebindEx: public virtual std::exception{
    public:
        virtual const char* what() const INFECTORPP_NOEXCEPT{
			return "\nCannot bind same interface twice\n";
        }
    };

	class INFECTORPP_API CircularDependencyEx: public virtual std::exception{
    public:
        virtual const char* what() const INFECTORPP_NOEXCEPT{
			return "\nCircular Dependency detected\n";
        }
    };
	
	class INFECTORPP_API TooDeepRecursionEx: public virtual std::exception{
    public:
        virtual const char* what() const INFECTORPP_NOEXCEPT{
			return "\nReached hard recursion limit\n";
        }
    };
	
	class INFECTORPP_API NotReachableEx: public virtual std::exception{
    public:
        virtual const char* what() const INFECTORPP_NOEXCEPT{
			return "\nThis is a infectorpp bug, report it at\n https://github.com/Darelbi/Infectorpp \n";
        }
    };
}
}