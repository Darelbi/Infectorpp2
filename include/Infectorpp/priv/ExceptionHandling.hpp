/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in InfectorTraits.hpp
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
	#undef INFECTORPP_CATCH
	#undef INFECTORPP_RETHROW
	#define INFECTORPP_TRY
	#define INFECTORPP_CATCH
	#define INFECTORPP_RETHROW
	
#else
	
	#undef INFECTORPP_TRY
	#undef INFECTORPP_CATCH
	#undef INFECTORPP_RETHROW
	#define INFECTORPP_TRY	try{
	#define INFECTORPP_CATCH }  catch ( std::exception& ex) {
	#define INFECTORPP_RETHROW throw ex; }

#endif

#ifndef _MSC_VER // Visual studio 2013 still does not support "noexcept"
                 // need a workaround thanks to  wtravisjones for bug report.
    #define INFECTORPP_NOEXCEPT noexcept(true)
#else
    #define NOEXCEPT
#endif

namespace Infector{
namespace priv{
	
	template< typename M>
	void throwOrBreak(){
		#ifdef INFECTORPP_DISABLE_EXCEPTION_HANDLING
			assert(false && M::what());
		#else
			throw M();
		#endif
	}
	
	class RebindEx: public virtual std::invalid_argument{
    public:
		RebindEx():std::invalid_argument(what()){ 		}
		
        virtual const char* what() const INFECTORPP_NOEXCEPT{
			return "\nCannot bind same interface twice\n";
        }
    };
	
	class CircularDependencyEx: public virtual std::invalid_argument{
    public:
		CircularDependencyEx():std::invalid_argument(what()){ 		}
		
        virtual const char* what() const INFECTORPP_NOEXCEPT{
			return "\nCircular Dependency detected\n";
        }
    };
	
}
}