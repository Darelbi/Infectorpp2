/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include <InfectorContainer.hpp>
#include <priv/ExceptionHandling.hpp>
#undef NDEBUG
#include <assert.h>

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
	ioc.bindAsNothing<classUsingMockedSharedPtr>();
	ioc.wire<classUsingMockedSharedPtr, Shared<buildSingleAsAbstract> >();
	auto context = ioc.createPrototypeContext();
	auto inst = std::make_shared<buildSingleAsConcrete>();
	context.registerMultiInstance<buildSingleAsConcrete,  buildSingleAsAbstract>(inst);
	auto mocked = context.build<classUsingMockedSharedPtr>(); // MOCKED CLASS SHOULD CALL MOCK METHOD
	assert(inst->wasMethodCalled()); //VERIFY MOCK METHOD WAS CALLED
	
	return 0;	
}