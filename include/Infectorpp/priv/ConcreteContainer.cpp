/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in InfectorTraits.hpp
*******************************************************************************/#include "ConcreteContainer.hpp"


namespace Infector {
namespace priv {

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
	INFECTORPP_CATCH
    
        //binding successfull till (i-1)th element then partial for i-th element
        bindingRollback( Bindings, interfaces, i);
		
	INFECTORPP_RETHROW
#endif
}



void ConcreteContainer::bindComponent
( 				TypeInfoP concrete,
				TypeInfoP interface,
				UpcastSignature * upcasts,
				std::size_t size){

	Bindings.bind(	std::make_tuple( concrete, upcasts[0], size), 
						interface);
	
}

void ConcreteContainer::wire
(                   TypeInfoP type,
                    BuildSignature func){

	Symbols.bind( func, type);
}

void ConcreteContainer::touch
(						TypeInfoP type, 
						TypeInfoP * deps, 
						std::size_t size) {
							
	std::size_t i = 0;

	INFECTORPP_TRY
	  
		Dependencies.setGuard( type);
        for(; i<size; i++)
			Dependencies.dependOn( type, deps[i], this);
		
#ifndef INFECTORPP_DISABLE_EXCEPTION_HANDLING			
	INFECTORPP_CATCH
    
        //binding successfull till (i-1)th element then partial for i-th element
        Dependencies.remove( type);
		
	INFECTORPP_RETHROW
#endif
}


virtual std::shared_ptr<Infector::Container> ConcreteContainer::split( std::shared_ptr<Infector::Container>& parent){
	
	return std::static_pointer_cast< Infector::Container> (
	
				std::make_shared( new ConcreteContainer( parent)
			);
}

virtual std::shared_ptr<Infector::Context> ConcreteContainer::createContext(){
	
	
}

TypeInfoP ConcreteContainer::getConcreteFromInterface( TypeInfoP interface){ 
//TODO: recursive up, and DAG should ask for that instead of memoizing 
//(at least on version 1 that don't need to be excessively optimized)
	auto concrete = Bindings.get(interface);
	return 
			Bindings.found(concrete)? 
									std::get<0>(concrete->second) 
								:	nullptr;
}

Container * createContainer(){
    return new ConcreteContainer();
}

void destroyContainer( Container * c){
    delete c;
}

} // namespace priv
} // namespace Infector
