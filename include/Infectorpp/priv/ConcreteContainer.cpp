/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/#include "ConcreteContainer.hpp"
#include "ConcreteContext.hpp"

namespace Infector {
namespace priv {


ConcreteContainer::ConcreteContainer()
	:dependencies( nullptr){

}

std::list<TypeInfoP> ConcreteContainer::getAbstractions( 
				std::type_index & concrete){
	if(!abstractions.found(
				abstractions.get( concrete))
	)
		throwOrBreak< NotReachableEx>();

	return abstractions.get( concrete)->second;
}

void ConcreteContainer::addAbstraction( TypeInfoP concrete, 
										TypeInfoP interface){

	if(!abstractions.found(
				abstractions.get( concrete))
	){
		std::list<TypeInfoP> interfaces;
		interfaces.push_back(interface);
		abstractions.bind(interfaces, concrete);
		return;
	}

	auto it = abstractions.get(concrete);
	it->second.push_back(interface);
}

void ConcreteContainer::removeAbstractions( TypeInfoP concrete, 
											TypeInfoP * interface,
											std::size_t max ){

	if(!abstractions.found(
				abstractions.get( concrete))
	)return;
	
	auto list = abstractions.get(concrete);
	for(std::size_t i = 0; i<=max; i++)
		list->second.remove( interface[i]);
}
	
void ConcreteContainer::bindSingleAs
(               TypeInfoP concrete,
                TypeInfoP * interfaces,
                SharedUpcastSignature * upcasts,
                std::size_t size){

    std::size_t i = 0; 
	std::size_t j = 0; 

	INFECTORPP_TRY

        for(; i<size;){
			bindings.bind( std::make_tuple( concrete, nullptr, upcasts[i], 0), interfaces[i]); //TODO :HER E NOT
			i++;
			addAbstraction( concrete, interfaces[j]);
			j++;
		}
		
#ifndef INFECTORPP_DISABLE_EXCEPTION_HANDLING	
	} catch( RebindEx & ex){
        //thrown when binding (bindings.bind()) the i-th element
		bindingRollback( bindings, interfaces, i);
		removeAbstractions( concrete, interfaces, j);
		throw ex;
		
	} catch ( std::exception & ex){ //thrown by abstractions or "out of memory"
		bindingRollback( bindings, interfaces, i);
		removeAbstractions( concrete, interfaces, j);
		throw ex;
	}
#endif
}



void ConcreteContainer::bindComponent
( 				TypeInfoP concrete,
				TypeInfoP interface,
				UpcastSignature upcast,
				std::size_t size){
					
	bool bindDone = false;

	INFECTORPP_TRY
	
		bindings.bind(	std::make_tuple( concrete, upcast, nullptr, size), 
						interface);
		bindDone = true;
		
		addAbstraction( concrete, interface);
	
	#ifndef INFECTORPP_DISABLE_EXCEPTION_HANDLING	
	} catch( RebindEx & ex){
		if(bindDone)
			bindings.remove( interface);
		throw ex;
		
	} catch ( std::exception & ex){
		if(bindDone)
			bindings.remove( interface);
		throw ex;
	}
	#endif
}

void ConcreteContainer::wire
(						TypeInfoP concrete, 
						TypeInfoP * deps, 
						std::size_t number,
						BuildSignature func,
						InstanceSignature inst) {
							
	if(!abstractions.found(
				abstractions.get( concrete))
	)
		throwOrBreak< NotBoundEx>();
		
	std::size_t i = 0;

	INFECTORPP_TRY
	  
		symbols.bind( func, concrete);
		instances.bind( inst, concrete);
		dependencies.setGuard( concrete);
		
        for(; i<number; i++)
			dependencies.dependOn( concrete, deps[i], this);
		
#ifndef INFECTORPP_DISABLE_EXCEPTION_HANDLING			
	} catch( CircularDependencyEx & ex){
		rollbackWire( concrete);
		throw ex;
	
	} catch( RebindEx & ex){
        rollbackWire( concrete);
		throw ex;
		
	} catch( std::exception & ex){
		rollbackWire( concrete);
		throw ex;
	}
#endif
}

void ConcreteContainer::rollbackWire(TypeInfoP type){
	dependencies.remove( type);
	instances.remove( type);
	symbols.remove( type);
}

DependencyDAG * ConcreteContainer::getGraph(){
	return &dependencies;
}

ContextPointer ConcreteContainer::createContext(){
	
	auto context =  std::make_shared< ConcreteContext>(
	
						std::move( bindings),
						std::move( symbols),
						std::move( instances),
						dependencies,
						(*this)
					);

	dependencies.clean();			
	return context;
}

TypeInfoP ConcreteContainer::getConcreteFromInterface( std::type_index & interface){ 
	auto concrete = bindings.get( interface);

	if(	bindings.found( concrete))
		return 	std::get<0>( concrete->second) ;

	return nullptr;
}

ConcreteContainer::~ConcreteContainer(){
	
}

ContainerPointer createContainer(){
    return std::move(  std::static_pointer_cast< priv::Container>(
					std::make_shared< ConcreteContainer>()
					)  );
}

} // namespace priv
} // namespace Infector
