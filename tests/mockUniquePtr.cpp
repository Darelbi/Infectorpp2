/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include <InfectorContainer.hpp>
#include <priv/ExceptionHandling.hpp>
#include "Catch.hpp"

class buildAsAbstract{
	
public:
	virtual int method() = 0;
	virtual ~buildAsAbstract(){}
};

class buildAsConcrete: public buildAsAbstract{
	
	bool methodCalled = false;
	
public:

	virtual int method(){ methodCalled=true; return 1;}
	bool wasMethodCalled() {return methodCalled;}
};



TEST_CASE( "mock unique ptr", "[infectorpp2]")
{
	using namespace Infector;
	
	Container ioc;
	
	ioc.bindAs<buildAsConcrete, buildAsAbstract>();
	ioc.wire<buildAsConcrete>();
	
	auto context = ioc.createPrototypeContext();
	
	auto abstract = context.build<buildAsAbstract>();
	REQUIRE( abstract->method() == 1);
	
	auto concrete = context.buildAs<buildAsAbstract, buildAsConcrete>();
	
	REQUIRE(concrete->method() ==1);
	REQUIRE(concrete->wasMethodCalled());
}