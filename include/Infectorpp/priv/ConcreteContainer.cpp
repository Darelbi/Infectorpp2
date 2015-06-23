/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in InfectorTraits.hpp
*******************************************************************************/#include "ConcreteContainer.hpp"


namespace Infector {
namespace priv {
	
ConcreteContainer::ConcreteContainer( priv::ContainerPointer p, DependencyDAG  * d)
	:Parent(p), Dependencies(d)
	{  }

ConcreteContainer::ConcreteContainer()
	:Parent( nullptr), Dependencies( nullptr){
	
}
	
void ConcreteContainer::bindSingleAs
(               TypeInfoP concrete,
                TypeInfoP * interfaces,
                UpcastSignature * upcasts,
                std::size_t size){

    std::size_t i = 0; 

	INFECTORPP_TRY

        for(; i<size; i++){
			Bindings.bind( std::make_tuple(concrete, upcasts[i], 0), interfaces[i]);
			//TODO: swap in DAG an abstract with its concrete?? not needed
			// but need DAG being able to check concretes from abstracts
		}
		
#ifndef INFECTORPP_DISABLE_EXCEPTION_HANDLING	
	} catch( RebindEx & ex){
    
        //binding successfull till (i-1)th element then partial for i-th element
        bindingRollback( Bindings, interfaces, i);
		throw ex;
	}
#endif
}



void ConcreteContainer::bindComponent
( 				TypeInfoP concrete,
				TypeInfoP interface,
				UpcastSignature upcast,
				std::size_t size){

	Bindings.bind(	std::make_tuple( concrete, upcast, size), 
						interface);
	
}

void ConcreteContainer::wire
(						TypeInfoP type, 
						TypeInfoP * deps, 
						std::size_t size,
						BuildSignature func) {
							
	std::size_t i = 0;

	INFECTORPP_TRY
	  
		Symbols.bind( func, type);
		Dependencies.setGuard( type);
        for(; i<size; i++)
			Dependencies.dependOn( type, deps[i], this);
		
#ifndef INFECTORPP_DISABLE_EXCEPTION_HANDLING			
	} catch( RebindEx & ex){
    
        //binding successfull till (i-1)th element then partial for i-th element
        rollbackWire(type);
		throw ex;
		
	} catch( std::exception & ex){
		
		rollbackWire(type);
		throw ex;
	}
#endif
}

void ConcreteContainer::rollbackWire(TypeInfoP type){
	
	Dependencies.remove( type);
	Symbols.remove( type);
}

DependencyDAG * ConcreteContainer::getGraph(){
	return &Dependencies;
}

ContainerPointer ConcreteContainer::split( ContainerPointer p){
	
	return std::move(  std::static_pointer_cast<priv::Container>(
					std::make_shared<ConcreteContainer>( p, &Dependencies)
					)  );
}

TypeInfoP ConcreteContainer::getConcreteFromInterface( TypeInfoP interface){ 

	auto concrete = Bindings.get( interface);
	return 
		Bindings.found( concrete)? 
							std::get<0>( concrete->second) 
						:	(Parent?
								Parent->getConcreteFromInterface(interface)
								: nullptr);
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
