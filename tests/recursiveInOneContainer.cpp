/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include <InfectorContainer.hpp>
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

struct FooFoo: public Foo{
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



int recursiveInOneContainer(int argc,char** argv){
	{
		using namespace Infector;
		Container ioc;
		
		ioc.bindSingleAs<FooBar, Foo>();
		ioc.bindAs<DependsOnFoo, AnotherInterface>();
		ioc.wire<FooBar>();
		ioc.wire<DependsOnFoo, 
						Shared<Foo> >();
	}
	
	return 0;
}