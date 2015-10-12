/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include <InfectorContainer.hpp>
#include <priv/ExceptionHandling.hpp>
#undef NDEBUG
#include <assert.h>

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

int bindSingleAsThree( int argc, char** const){
	
	using namespace Infector;
	
	Container ioc;
	ioc.bindSingleAs< ABC, ServiceA, ServiceB, ServiceC>();
	
	ioc.wire< ABC>();

	auto context = ioc.createPrototypeContext();

	auto A = context.buildSingle< ServiceA>();
	auto B = context.buildSingle< ServiceB>();
	auto C = context.buildSingle< ServiceC>();
	
	assert( A->asA() == B->asB());
	assert( C->asC() == B->asB());
	assert( A->asA() != nullptr);

	return 0;
}