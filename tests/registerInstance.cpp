/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include <InfectorContainer.hpp>
#include <priv/ExceptionHandling.hpp>
#include "Catch.hpp"

class registerInstanceClass{
public:
	int method(){return 0;}
};

TEST_CASE( "register concrete instance", "[infectorpp2]")
{
	using namespace Infector;
	
	Container ioc;
	
	auto context = ioc.createPrototypeContext();
	context.registerInstance( std::make_shared<registerInstanceClass>());
	auto inst = context.buildSingle<registerInstanceClass>();

	REQUIRE(inst->method() == 0);
}