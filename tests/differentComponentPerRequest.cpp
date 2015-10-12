/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include <InfectorContainer.hpp>
#include <priv/ExceptionHandling.hpp>
#undef NDEBUG
#include <assert.h>


class differentComponentInterface{
public:
	virtual ~differentComponentInterface(){}
	
	virtual void aMethod() = 0;
};

class differentComponentInstance: public differentComponentInterface{
public:
	differentComponentInstance(){};
	
	void aMethod() override{}
};

int differentComponentPerRequest(int argc, char ** const){
	
	using namespace Infector;
	
	Container ioc;
	ioc.bindAs< differentComponentInstance, differentComponentInterface>();
	
	ioc.wire<differentComponentInstance>();

	auto context = ioc.createPrototypeContext();
	
	std::unique_ptr<differentComponentInterface> components[10];
	
	for(int i=0; i<10;i++)
		components[i] = context.build<differentComponentInterface>();
	
	for(int i=0; i<10;i++)
		for(int j=0; j<10;j++)
			if(i!=j)
				assert( components[i] != components[j]);
	return 0;
}