/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include <InfectorContainer.hpp>
#include <priv/ExceptionHandling.hpp>
#undef NDEBUG
#include <assert.h>
#include "TestHelper.hpp"

class SelfRecursiveAbstract{
	public:
	~SelfRecursiveAbstract(){}
	
	virtual void method() = 0;
	
};

class SelfRecursive: public SelfRecursiveAbstract{
	
	public:
	
	SelfRecursive(std::unique_ptr<SelfRecursiveAbstract>){}
	
	virtual void method() override{}
	
};

int selfRecursiveAbstract(int argc, char **){
	
	using namespace Infector;
	
	Container ioc;
	
	ioc.bindAs< SelfRecursive, SelfRecursiveAbstract> ();
	
	
	try{
		ioc.wire<  SelfRecursive, Unique<SelfRecursiveAbstract> >();
		assert(false); //test failed
	}
	catch( const priv::CircularDependencyEx &ex){
		
	}
	catch(...){
		assert(false); //test failed
	}
	
	
	return 0;
}