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

std::shared_ptr<void> ConcreteContext::instance( TypeInfoP type){
	
}

void * ConcreteContext::buildComponent( TypeInfoP type){
	
}
	
} // namespace priv
} // namespace Infector