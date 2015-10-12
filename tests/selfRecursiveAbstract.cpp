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

TEST_CASE( "self recursive abstract", "[infectorpp2]")
{	
	using namespace Infector;
	
	Container ioc;
	
	ioc.bindAs< SelfRecursive2, SelfRecursiveAbstract> ();
	
	REQUIRE_THROWS( ioc.wire<  SelfRecursive2, 
								Unique< SelfRecursiveAbstract> >());

}