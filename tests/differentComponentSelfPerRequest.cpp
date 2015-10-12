/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include <InfectorContainer.hpp>
#include <priv/ExceptionHandling.hpp>
#include "Catch.hpp"


class differentComponentSelfInstance{
public:
	differentComponentSelfInstance(){};
	
	void aMethod() {}
};

TEST_CASE( "check that built components are different", "[infectorpp2]")
{
	using namespace Infector;
	
	Container ioc;
	ioc.bindAsNothing< differentComponentSelfInstance>();
	
	ioc.wire<differentComponentSelfInstance>();

	auto context = ioc.createPrototypeContext();
	
	std::unique_ptr<differentComponentSelfInstance> components[10];
	
	SECTION("instantiate 10 components")
	{
		for(int i=0; i<10;i++){
			components[i] = context.build<differentComponentSelfInstance>();
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