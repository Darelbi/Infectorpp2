/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include <InfectorContainer.hpp>
#include <priv/ExceptionHandling.hpp>
#undef NDEBUG
#include <assert.h>
#include "TestHelper.hpp"

class buildAsAbstract{
	
public:
	virtual int method() = 0;
	virtual ~buildAsAbstract(){}
};

class buildAsConcrete: public buildAsAbstract{
	
	bool methodCalled = false;
	
public:

	virtual int method(){ methodCalled=true; return 1;}
	bool wasMethodCalled() {return methodCalled;}
};




int mockUniquePtr(int , char** ){
	
	using namespace Infector;
	
	Container ioc;
	
	ioc.bindAs<buildAsConcrete, buildAsAbstract>();
	ioc.wire<buildAsConcrete>();
	
	auto context = ioc.createPrototypeContext();
	
	auto abstract = context.build<buildAsAbstract>();
	assert( abstract->method() == 1);
	
	auto concrete = context.buildAs<buildAsAbstract, buildAsConcrete>();
	
	//std::unique_ptr<buildAsAbstract> casted = std::move(concrete);
	
	assert(concrete->method() ==1);
	assert(concrete->wasMethodCalled());

	
	return 0;	
}