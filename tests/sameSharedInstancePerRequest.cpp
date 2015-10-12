/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include <InfectorContainer.hpp>
#include <priv/ExceptionHandling.hpp>
#undef NDEBUG
#include <assert.h>

	
class sameSharedInterface{
public:
	virtual ~sameSharedInterface(){}
	
	virtual void aMethod() = 0;
};

class sameSharedInstance: public sameSharedInterface{
public:
	sameSharedInstance(){};
	
	void aMethod() override{}
};


int sameSharedInstancePerRequest(int argc, char** const){
	
	
	using namespace Infector;
	
	Container ioc;
	ioc.bindSingleAs< sameSharedInstance, sameSharedInterface>();
	
	ioc.wire<sameSharedInstance>();

	auto context = ioc.createPrototypeContext();

	auto instance = context.buildSingle<sameSharedInterface>();

	for(int i=0; i<10;i++)
		assert( instance == context.buildSingle<sameSharedInterface>());

	return 0;
}