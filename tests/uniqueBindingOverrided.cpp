/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include <InfectorContainer.hpp>
#include <priv/ExceptionHandling.hpp>
#undef NDEBUG
#include <assert.h>
#include "TestHelper.hpp"

ABSTRACT_CLASS( uniqueBindingOverridedAbstract)
CONCRETE_CLASS( concreteBindingOverrided, uniqueBindingOverridedAbstract, void)


class concreteBindingOverrided2: public uniqueBindingOverridedAbstract{
	
public:
	concreteBindingOverrided2(){}
	
	virtual int method() override	
	{ 
		return 1;
	}			
};

int uniqueBindingOverrided(int argc, char**){
	
	using namespace Infector;
	
	Container c1;
	
	c1.bindAs< concreteBindingOverrided, uniqueBindingOverridedAbstract >();
	c1.wire< concreteBindingOverrided>();
	
	auto c2 = c1.splitContainer();
	c2.bindAs< concreteBindingOverrided2, uniqueBindingOverridedAbstract>();
	c2.wire< concreteBindingOverrided2>();
	
	auto ctx1 = c1.createPrototypeContext();
	auto ctx2 = c2.createPrototypeContext();
	
	auto inst1 = ctx1.build< uniqueBindingOverridedAbstract>();
	auto inst2 = ctx2.build< uniqueBindingOverridedAbstract>();
	
	assert(inst1->method() == 0);
	assert(inst2->method() == 1);
	
	return 0;
}