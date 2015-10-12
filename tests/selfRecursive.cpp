/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include <InfectorContainer.hpp>
#include <priv/ExceptionHandling.hpp>
#include "Catch.hpp"

class SelfRecursive{
	
	public:
	
	SelfRecursive(std::unique_ptr<SelfRecursive>){}
	
	void method(){}
	
};

TEST_CASE( "self recursive", "[infectorpp2]")
{	
	using namespace Infector;
	
	Container ioc;
	
	ioc.bindAsNothing< SelfRecursive> ();
	
	REQUIRE_THROWS( ioc.wire<  SelfRecursive, Unique< SelfRecursive> >());
}