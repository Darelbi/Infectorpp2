/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include <InfectorContainer.hpp>
#include <priv/ExceptionHandling.hpp>
#undef NDEBUG
#include <assert.h>
#include "TestHelper.hpp"

ABSTRACT_CLASS( InheritDepOnce)
CONCRETE_CLASS( ConcreteInheritDepOnce, InheritDepOnce, void)

ABSTRACT_CLASS( InheritDependerOnce)
CONCRETE_CLASS( ConcreteInheritDependerOnce, InheritDependerOnce,
				std::shared_ptr<InheritDepOnce>)

int inheritDependencyOnce( int argc, char **){
	
	using namespace Infector;
	
	Container c1;
	c1.bindSingleAs< ConcreteInheritDepOnce, InheritDepOnce>();
	c1.wire< ConcreteInheritDepOnce>();
	
	auto c2 = c1.splitContainer();
	
	c2.bindAs< ConcreteInheritDependerOnce, InheritDependerOnce>();
	c2.wire< ConcreteInheritDependerOnce, Shared<InheritDepOnce> >();
	
	auto ctx1 = c1.createPrototypeContext();
	auto ctx2 = c2.createPrototypeContext();
	
	//todo: make it a feature or fix the bug? (build fail because dependency not in symbol table)
	//need a method in container to lookup parent to fill a SymbolTableEntry.. TODO MOVE INTO CONTAINER
	// (bytecode is cache local, the constructor of context pollutes instruction cache)
	auto inst = ctx2.build< InheritDependerOnce>();
	
	assert(inst->method() == 0);
	
	return 0;
}