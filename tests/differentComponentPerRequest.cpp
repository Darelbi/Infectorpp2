/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include <InfectorContainer.hpp>
#include <priv/ExceptionHandling.hpp>
#include "Catch.hpp"


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

TEST_CASE( "check that built abstract components are different", "[infectorpp2]")
{
	using namespace Infector;
	
	Container ioc;
	ioc.bindAs< differentComponentInstance, differentComponentInterface>();
	
	ioc.wire<differentComponentInstance>();

	auto context = ioc.createPrototypeContext();
	
	std::unique_ptr<differentComponentInterface> components[10];
	
	SECTION("instantiate 10 components")
	{
		for(int i=0; i<10;i++){
			components[i] = context.build<differentComponentInterface>();
			REQUIRE(components[i] != nullptr);
		}
		
		SECTION(" check if components are different")
		{
			for(int i=0; i<10;i++)
				for(int j=0; j<10;j++)
					if(i!=j)
						REQUIRE( components[i] != components[j]);
		}
	}
}