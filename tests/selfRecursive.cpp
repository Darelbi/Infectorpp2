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

namespace {
	
	void wire( Infector::Container & ioc){
		 ioc.wire<  SelfRecursive, Infector::Unique< SelfRecursive> >();
	}
}

TEST_CASE( "self recursive", "[infectorpp2]")
{	
	Infector::Container ioc;
	
	ioc.bindAsNothing< SelfRecursive> ();
	
	REQUIRE_THROWS( wire(ioc));
}