/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/#include "ConcreteContainer.hpp"
#include "ConcreteContext.hpp"


namespace Infector {
namespace priv {
	
ConcreteContainer::ConcreteContainer( 	priv::ContainerPointer p, 
										DependencyDAG  * d,
										std::shared_ptr<bool> locker)
	:parent(p), dependencies(d), bindingLock(locker)
	{  }

ConcreteContainer::ConcreteContainer()
	:parent( nullptr), dependencies( nullptr)
		, bindingLock( std::make_shared<bool>(false)){
	
}
	
void ConcreteContainer::bindSingleAs
(               TypeInfoP concrete,
                TypeInfoP * interfaces,
                SharedUpcastSignature * upcasts,
                std::size_t size){

    std::size_t i = 0; 

	INFECTORPP_TRY

        for(; i<size; i++){
			bindings.bind( std::make_tuple( concrete, nullptr, upcasts[i], 0), interfaces[i]); //TODO :HER E NOT
			//TODO: swap in DAG an abstract with its concrete?? not needed
			// but need DAG being able to check concretes from abstracts
		}
		
#ifndef INFECTORPP_DISABLE_EXCEPTION_HANDLING	
	} catch( RebindEx & ex){
    
        //binding successfull till (i-1)th element then partial for i-th element
		if( i>0)
			bindingRollback( bindings, interfaces, i-1);
		throw ex;
	}
#endif
}



void ConcreteContainer::bindComponent
( 				TypeInfoP concrete,
				TypeInfoP interface,
				UpcastSignature upcast,
				std::size_t size){

	bindings.bind(	std::make_tuple( concrete, upcast, nullptr, size), 
						interface);
	
}

void ConcreteContainer::wire
(						TypeInfoP type, 
						TypeInfoP * deps, 
						std::size_t size,
						BuildSignature func,
						InstanceSignature inst) {
							
	std::size_t i = 0;

	INFECTORPP_TRY
	  
		symbols.bind( func, type);
		instances.bind( inst, type);
		dependencies.setGuard( type);
		
        for(; i<size; i++)
			dependencies.dependOn( type, deps[i], this);
		
#ifndef INFECTORPP_DISABLE_EXCEPTION_HANDLING			
	} catch( CircularDependencyEx & ex){
		rollbackWire( type);
		throw ex;
	
	} catch( RebindEx & ex){
        rollbackWire( type);
		throw ex;
		
	} catch( std::exception & ex){
		rollbackWire( type);
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

ContainerPointer ConcreteContainer::split( 	ContainerPointer p){
	
	return std::move(  std::static_pointer_cast<priv::Container>(
					std::make_shared<ConcreteContainer>(	p, 
															&dependencies,
															bindingLock)
					)  );
}

void ConcreteContainer::checkLock(){
	if((*bindingLock) == true)
		throwOrBreak<ContainerLockedEx>();
}

void ConcreteContainer::lock(){
	(*bindingLock) = true;
}

ContextPointer ConcreteContainer::createContext(){
	parent = nullptr;
	
	auto context =  std::make_shared< ConcreteContext>(
	
						std::move( bindings),
						std::move( symbols),
						std::move( instances),
						dependencies
					);
											
	dependencies.clean();									
	return context;
}

TypeInfoP ConcreteContainer::getConcreteFromInterface( TypeInfoP interface){ 
	auto concrete = bindings.get( interface);

	if(	bindings.found( concrete))
		return 	std::get<0>( concrete->second) ;

	return parent!=nullptr?
			parent->getConcreteFromInterface(interface):
			nullptr;
}

ConcreteContainer::~ConcreteContainer(){
	
}

ContainerPointer createContainer(){
    return std::move(  std::static_pointer_cast<priv::Container>(
					std::make_shared<ConcreteContainer>()
					)  );
}

} // namespace priv
} // namespace Infector
