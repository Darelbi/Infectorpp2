/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include <InfectorContainer.hpp>
#include <priv/ExceptionHandling.hpp>
#include "Catch.hpp"

	
class sameSharedInterface{
public:
	virtual ~sameSharedInterface(){}
	
	virtual void aMethod() = 0;
};

class sameSharedInstance: public sameSharedInterface{
public:
	sameSharedInstance(){};
	
	void aMethod() override{}
};

TEST_CASE( "same shared instance per request", "[infectorpp2]")
{
	using namespace Infector;
	
	Container ioc;
	ioc.bindSingleAs< sameSharedInstance, sameSharedInterface>();
	
	ioc.wire<sameSharedInstance>();

	auto context = ioc.createPrototypeContext();

	auto instance = context.buildSingle<sameSharedInterface>();

	for(int i=0; i<10;i++)
		REQUIRE( instance == context.buildSingle<sameSharedInterface>());
}