/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include <InfectorContainer.hpp>
#include <priv/ExceptionHandling.hpp>
#undef NDEBUG
#include <assert.h>
#include "TestHelper.hpp"

class SelfRecursive{
	
	public:
	
	SelfRecursive(std::unique_ptr<SelfRecursive>){}
	
	void method(){}
	
};

int selfRecursive(int argc, char ** const){
	
	using namespace Infector;
	
	Container ioc;
	
	ioc.bindAsNothing< SelfRecursive> ();
	
	
	try{
		ioc.wire<  SelfRecursive, Unique<SelfRecursive> >();
		assert(false); //test failed
	}
	catch( const priv::CircularDependencyEx &ex){
		
	}
	catch(...){
		assert(false); //test failed
	}
	
	
	return 0;
}