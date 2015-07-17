/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include <InfectorContainer.hpp>
#include <priv/ExceptionHandling.hpp>
#undef NDEBUG
#include <assert.h>
#include "TestHelper.hpp"

ABSTRACT_CLASS( sharedBindingOverridedAbstract)
CONCRETE_CLASS( concreteSharedBindingOverrided, sharedBindingOverridedAbstract, void)


class concreteSharedBindingOverrided2: public sharedBindingOverridedAbstract{
	
public:
	concreteSharedBindingOverrided2(){}
	
	virtual int method() override	
	{ 
		return 1;
	}			
};

int sharedBindingOverrided(int argc, char**){
	
	using namespace Infector;
	
	Container c1;
	
	c1.bindSingleAs< concreteSharedBindingOverrided, sharedBindingOverridedAbstract >();
	c1.wire< concreteSharedBindingOverrided>();
	
	auto c2 = c1.splitContainer();
	c2.bindSingleAs< concreteSharedBindingOverrided2, sharedBindingOverridedAbstract>();
	c2.wire< concreteSharedBindingOverrided2>();
	
	auto ctx1 = c1.createPrototypeContext();
	auto ctx2 = c2.createPrototypeContext();
	
	auto inst1 = ctx1.buildSingle< sharedBindingOverridedAbstract>();
	auto inst2 = ctx2.buildSingle< sharedBindingOverridedAbstract>();
	
	assert(inst1->method() == 0);
	assert(inst2->method() == 1);
	
	return 0;
}