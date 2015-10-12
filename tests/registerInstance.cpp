/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include <InfectorContainer.hpp>
#include <priv/ExceptionHandling.hpp>
#undef NDEBUG
#include <assert.h>
#include "TestHelper.hpp"
#include <iostream>
#define LOG(x) std::cerr<< x <<std::endl;

class registerInstanceClass{
public:
	int method(){return 0;}
};

int registerInstance(int, char** const){
	
	using namespace Infector;
	
	Container ioc;
	LOG("1")
	auto context = ioc.createPrototypeContext();
	LOG("2")
	context.registerInstance( std::make_shared<registerInstanceClass>());
	LOG("3")
	auto inst = context.buildSingle<registerInstanceClass>();
	LOG("4")
	assert(inst->method() == 0);
	
	
	return 0;
}