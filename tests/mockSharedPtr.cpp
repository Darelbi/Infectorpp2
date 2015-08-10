/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include <InfectorContainer.hpp>
#include <priv/ExceptionHandling.hpp>
#undef NDEBUG
#include <assert.h>
#include <iostream>
#define LOG(x) std::cerr<< x <<std::endl;

#include "TestHelper.hpp"

class buildSingleAsAbstract{
	
public:
	virtual int method() = 0;
	virtual ~buildSingleAsAbstract(){}
};

class buildSingleAsConcrete: public buildSingleAsAbstract{
	
	bool methodCalled = false;
	
public:

	virtual int method(){ methodCalled=true; return 1;}
	bool wasMethodCalled() {return methodCalled;}
};

class classUsingMockedSharedPtr{
public:

	classUsingMockedSharedPtr(std::shared_ptr<buildSingleAsAbstract> ptr){
		ptr->method();
	}
	
};




int mockSharedPtr(int , char** ){
	
	using namespace Infector;
	
	Container ioc;
	
	ioc.bindSingleAsNothing<classUsingMockedSharedPtr>();
	ioc.wire<classUsingMockedSharedPtr, Shared<buildSingleAsAbstract> >();
	LOG("1")
	auto context = ioc.createPrototypeContext();
	LOG("2")
	auto inst = std::make_shared<buildSingleAsConcrete>();
	LOG("3")
	context.registerMultiInstance<buildSingleAsConcrete,  buildSingleAsAbstract>(inst);
	LOG("4")
	auto mocked = context.build<classUsingMockedSharedPtr>(); // MOCKED CLASS SHOULD CALL MOCK METHOD
	LOG("5")
	auto inst2 = context.buildAs<buildSingleAsAbstract, buildSingleAsConcrete>();
	LOG("6")
	assert(inst2->wasMethodCalled()); //VERIFY MOCK METHOD WAS CALLED

	
	return 0;	
}