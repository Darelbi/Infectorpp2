/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include <InfectorContainer.hpp>
#include <priv/ExceptionHandling.hpp>
#undef NDEBUG
#include <assert.h>
#include "TestHelper.hpp"

class registerInstanceClass{
public:
	int method(){return 0;}
};

int registerInstance(int, char**){
	
	using namespace Infector;
	
	Container ioc;
	
	auto context = ioc.createPrototypeContext();
	
	context.registerInstance( std::make_shared<registerInstanceClass>());
	
	auto inst = context.buildSingle<registerInstanceClass>();
	assert(inst->method() == 0);
	
	
	return 0;
}