/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include <InfectorContainer.hpp>
#include <priv/ExceptionHandling.hpp>
#undef NDEBUG
#include <assert.h>


class differentComponentSelfInstance{
public:
	differentComponentSelfInstance(){};
	
	void aMethod() {}
};

int differentComponentSelfPerRequest(int argc, char ** argv){
	
	using namespace Infector;
	
	Container ioc;
	ioc.bindAsNothing< differentComponentSelfInstance>();
	
	ioc.wire<differentComponentSelfInstance>();

	auto context = ioc.createPrototypeContext();
	
	std::unique_ptr<differentComponentSelfInstance> components[10];
	
	for(int i=0; i<10;i++)
		components[i] = context.build<differentComponentSelfInstance>();
	
	for(int i=0; i<10;i++)
		for(int j=0; j<10;j++)
			if(i!=j)
				assert( components[i] != components[j]);
	return 0;
}