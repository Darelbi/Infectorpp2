/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include <InfectorContainer.hpp>
#include <priv/ExceptionHandling.hpp>
#undef NDEBUG
#include <assert.h>
#include <iostream>

#define LOG( X ) std::cerr<< X <<std::endl;



struct Interface1{

};

struct Foo{
	virtual void doFoo() = 0;
};

struct FooBar: public Foo{
	virtual void doFoo() override{
		
	}
};

struct AnotherInterface{
	virtual void doSomething() = 0;
};

struct DependsOnFoo: public AnotherInterface{
	DependsOnFoo( std::shared_ptr<Foo> a){}

	virtual void doSomething() override{

	}
};

struct NoDep: public AnotherInterface{

	virtual void doSomething() override{

	}
};

struct FooFoo: public Foo{
	
	FooFoo( std::unique_ptr<AnotherInterface>){}
	virtual void doFoo() override{

	}
};


int recursiveInOneContainer(int argc,char** argv){

	using namespace Infector;
	Container ioc;
	
	ioc.bindSingleAs< FooFoo, Foo>();
	ioc.bindAs< NoDep, AnotherInterface>();
	ioc.wire< FooFoo, 
					Unique< AnotherInterface>		>();
	ioc.wire<NoDep>();

	auto ioc2 = ioc.splitContainer();

	ioc2.bindAs< DependsOnFoo, AnotherInterface>();

	try{
		ioc2.wire< DependsOnFoo, Shared<Foo> >();
	}
	catch(priv::CircularDependencyEx &ex){

	}
	catch(...){
		assert(false); //test failed
	}

	return 0;
}