/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include <InfectorContainer.hpp>
#include <priv/ExceptionHandling.hpp>
#include "Catch.hpp"

class ServiceA{
	
	public:
		virtual	~ServiceA(){}
		
		virtual void * asA() = 0;
};

class ServiceB{
	
	public:
		virtual	~ServiceB(){}
		
		virtual void * asB() = 0;
};

class ServiceC{
	
	public:
		virtual	~ServiceC(){}
		
		virtual void * asC() = 0;
};

class ABC: public ServiceA, public ServiceB, public ServiceC {
	
	int val = 3;
	
public:
	ABC(){
		
	}
	
	void * asA() override { return val==3? this: nullptr; }
	void * asB() override { return val==3? this: nullptr; }
	void * asC() override { return val==3? this: nullptr; }
};

TEST_CASE( "bind single service as 3 interfaces", ""[infectorpp2]"")
{
	using namespace Infector;
	
	Container ioc;
	ioc.bindSingleAs< ABC, ServiceA, ServiceB, ServiceC>();
	
	ioc.wire< ABC>();

	auto context = ioc.createPrototypeContext();

	auto A = context.buildSingle< ServiceA>();
	auto B = context.buildSingle< ServiceB>();
	auto C = context.buildSingle< ServiceC>();
	
	REQUIRE( A != nullptr);
	REQUIRE( B != nullptr);
	REQUIRE( C != nullptr);
	
	SECTION(" check return values to see if instantiation is correct")
	{
		REQUIRE( A->asA() == B->asB());
		REQUIRE( C->asC() == B->asB());
		REQUIRE( A->asA() != nullptr);
	}
}