/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include <InfectorContainer.hpp>
#include <priv/ExceptionHandling.hpp>
#include "Catch.hpp"

class sameSharedSelfInstance{
public:
	sameSharedSelfInstance(){};
	
	void aMethod() {}
};


TEST_CASE( "same shared self instance per request", "[infectorpp2]")
{
	using namespace Infector;
	
	Container ioc;
	ioc.bindSingleAsNothing< sameSharedSelfInstance>();
	
	ioc.wire<sameSharedSelfInstance>();

	auto context = ioc.createPrototypeContext();

	auto instance = context.buildSingle<sameSharedSelfInstance>();

	for(int i=0; i<10;i++)
		REQUIRE( instance == context.buildSingle<sameSharedSelfInstance>());
}