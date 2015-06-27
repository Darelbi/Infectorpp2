/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include "ConcreteContext.hpp"

namespace Infector{
namespace priv{
	
void ConcreteContext::mockFunctionAndPushDownRestore
							( FuncP * toBeMocked, FuncP newFunc){
								
}
								
void ConcreteContext::registerInstance( std::shared_ptr<void> inst,
							TypeInfoP type){
								
								
}

std::shared_ptr<void> ConcreteContext::instance( TypeInfoP interface){
	
	auto &it = instances.find( std::type_index(*interface))->second;
	if(it.instance != nullptr)
		return it.instance;
	
	throwingAssertion<InstantiatingComponentEx>(it.size==0);
	
	return 
		it.instance = std::shared_ptr<void>( 
										it.toBaseConversion( // USARE INSTANCES_FACTORY_FUNCTION_HERE
											it.constructor(this)) //TODO: NOOOO!!!! devo poter chiamare il distruttore. Quindi la 
																// factory function deve creare uno shared_ptr del tipo esatto
											);
}

void * ConcreteContext::buildComponent( TypeInfoP type){
	
}

ConcreteContext::ConcreteContext(	ConcreteContainer::TypeBinding types,
									ConcreteContainer::SymbolTable symbols ){

						
}
	
} // namespace priv
} // namespace Infector