/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include <InfectorContainer.hpp>
#include <priv/ExceptionHandling.hpp>
#include "Catch.hpp"

class SelfRecursiveAbstract{
	public:
	~SelfRecursiveAbstract(){}
	
	virtual void method() = 0;
	
};

class SelfRecursive2: public SelfRecursiveAbstract{
	
	public:
	
	SelfRecursive2(std::unique_ptr<SelfRecursiveAbstract>){}
	
	virtual void method() override{}
	
};

namespace{
	
	void wire( Infector::Container & ioc){
		 ioc.wire<  SelfRecursive2, //comma is a problem inside macros
								Infector::Unique< SelfRecursiveAbstract> >();
	}
}

TEST_CASE( "self recursive abstract", "[infectorpp2]")
{	
	Infector::Container ioc;
	
	ioc.bindAs< SelfRecursive2, SelfRecursiveAbstract> ();
	
	REQUIRE_THROWS( wire(ioc));

}