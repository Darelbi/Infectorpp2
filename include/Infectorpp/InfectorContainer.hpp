/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "InfectorTraits.hpp"
#include "InfectorContext.hpp"
#include "priv/InfectorAbstractContainer.hpp"


namespace Infector {

class Container{
public:

    /** Declare a type as implementation of multiple interfaces(Contracts).
    *   This type will be injected using a "std::shared_ptr", only 1 istance of
    *   T will be created and shared within a context.*/
    template< typename Impl, typename... Contracts>
    void bindSingleAs();

    /** Declare a type as implementation of 1 interface (Contract).
    *   "std::unique_ptr" will be used to inject instances of this object, each
    *   time this type is requested a new instance is created.*/
    template< typename Impl, typename Contract>
    void bindAs();

    /** Wire a type to its dependencies so that it becomes constructible and
    *   injectable without having to pass further parameters to its constructor
    *   Note that during this phase a circular dependency check is performed.*/
    template< typename Impl, typename... Dependencies>
    void wire();

    /**========================================
                      ADVANCED USE:
    ===========================================*/



    /** HIERARCHY:
		Create a child container from this one. You keep parent container
		as sort of "preset" but you can make changes in the child (so
		you can wire and bind different types and constructors)

		The purpose is to allow mocking and to allow reusing part of
		application configuration minimizing changes needed.
		*/
    Container splitContainer();

    /** HIERARCHY:
		Once a context is created from any point of the hierarchy
		the whole hierarchy becomes locked (cannot longer be splitted
		or binded ). You can still register and instantiate instances.
		Each container can spawm multiple contexts and has a unique
		type binding.*/
    Context createContext();



    /**========================================
                       DETAILS:
    ===========================================*/

    Container();
	
	virtual ~Container() = default;

private:

	Container( priv::ContainerPointer p);

    priv::ContainerPointer          container; // Implementation
};

inline Container::Container()
    :
    container(   priv::createContainer() ){

}

inline Container::Container( priv::ContainerPointer p)
	:
	container( p){
	
}

template< typename T, typename... Contracts>
void Container::bindSingleAs(){

    isMultiBase< T, Contracts...>(); //compile time test

    priv::TypeInfoP         types[ sizeof...( Contracts)]
                        { &typeid( Contracts)... };

    priv::SharedUpcastSignature upcasts[ sizeof...( Contracts)]
                        { &priv::shared_upcast< T, Contracts>... };

    container->bindSingleAs( &typeid(T), types, upcasts, sizeof...( Contracts));
}

template< typename T, typename A>
void Container::bindAs(){

    isMultiBase< T, A>(); //compile time test // TODO: NO!!! allow bind as nothing

    container->bindComponent( &typeid(T), &typeid(A), 
							&priv::upcast< T, A>, sizeof(T));
}


template< typename Impl, typename... SmartPointers>
void Container::wire(){

	isWireable< Impl>(); //compile time test

    priv::TypeInfoP types[ sizeof...( SmartPointers)]
                        { &typeid(typename SmartPointers::type)... };
						
	container->wire( &typeid(Impl), types, sizeof...( SmartPointers),
					 &factoryFunction< Impl, SmartPointers...>,
					 &instancesFactoryFunction< Impl, SmartPointers...>);
					
	//TODO. make pair (upcast, and new concrete instance togheter) (when compile context)
}

Container Container::splitContainer(){
	
	return Container( container->split( container));
}

Context Container::createContext(){
	
	return Context( container->createContext());
}

} // namespace Infector
