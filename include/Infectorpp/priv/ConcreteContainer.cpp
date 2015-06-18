/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in InfectorExport.hpp
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
		
	INFECTORPP_CATCH
    
        //binding successfull till (i-1)th element then partial for i-th element
        bindingRollback( Bindings, interfaces, i);
		
	INFECTORPP_RETHROW
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
			
	INFECTORPP_CATCH
    
        //binding successfull till (i-1)th element then partial for i-th element
        Dependencies.remove( type);
		
	INFECTORPP_RETHROW
}

TypeInfoP ConcreteContainer::getConcreteFromInterface( TypeInfoP interface){
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
