/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include <InfectorContainer.hpp>
#include <priv/ExceptionHandling.hpp>
#undef NDEBUG
#include <assert.h>


class sameSharedSelfInstance{
public:
	sameSharedSelfInstance(){};
	
	void aMethod() {}
};


int sameSharedSelfInstancePerRequest(int argc, char** const){
	
	
	using namespace Infector;
	
	Container ioc;
	ioc.bindSingleAsNothing< sameSharedSelfInstance>();
	
	ioc.wire<sameSharedSelfInstance>();

	auto context = ioc.createPrototypeContext();

	auto instance = context.buildSingle<sameSharedSelfInstance>();

	for(int i=0; i<10;i++)
		assert( instance == context.buildSingle<sameSharedSelfInstance>());

	return 0;
}