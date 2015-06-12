/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in InfectorExport.hpp
*******************************************************************************/
#include <exception>

//uncomment following line to disable all TRY / CATCH clauses inside Infectorpp

//#define INFECTORPP_DISABLE_EXCEPTION_HANDLING 1

// (you need to recompile Infectorpp)..

// ..Alternatively Cmake GUI has the checkbox option for that

#ifdef INFECTORPP_DISABLE_EXCEPTION_HANDLING
	#undef NDEBUG
	#include <assert.h>

	#define INFECTORPP_CONDITIONAL_EXCEPTION( body, rollback)  {body}
	
	#define INFECTORPP_CONDITIONAL_THROW ( condition, ex, message) \
		assert(false && message);
	
#else
	
	#define INFECTORPP_CONDITIONAL_EXCEPTION( body, rollback) \
	try{ body } catch ( std::exception& ex) { rollback }
	
	#define INFECTORPP_CONDITIONAL_THROW ( condition, ex, message) \
		if( condition) throw ex(message);

#endif

namespace Infector{
namespace priv{
	
	class RebindEx{
		public:
		static const char * message(){
			"\nCannot bind same interface twice\n";
		}
	};
	
}
}