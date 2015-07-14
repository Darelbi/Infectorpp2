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
    *   IMPL will be created and shared within a context.*/
    template< typename Impl, typename... Contracts>
    void bindSingleAs();
	
	/** This type will be injected using a "std::shared_ptr", only 1 istance of
    *   IMPL will be created and shared within a context as IMPL*/
    template< typename Impl>
    void bindSingleAsNothing();

    /** Declare a type as implementation of 1 interface (Contract).
    *   "std::unique_ptr" will be used to inject instances of this object, each
    *   time this type is requested a new instance is created.*/
    template< typename Impl, typename Contract>
    void bindAs();
	
	/** Declare a type as implementation of 1 interface (Contract).
    *   "std::unique_ptr" will be used to inject instances of this object, each
    *   time this type is requested a new instance is created.*/
    template< typename Impl>
    void bindAsNothing();

    /** Wire a type to its dependencies so that it becomes constructible and
    *   injectable without having to pass further parameters to its constructor
    *   Note that during this phase a circular dependency check is performed.*/
    template< typename Impl, typename... Dependencies>
    void wire();
	
	/** Create a context and KILL CONTAINER HIERARCHY (if you need more than one
	*	context you have to clone it).*/
	Context createPrototypeContext();

    /**========================================
                      ADVANCED USE:
    ===========================================*/



    /** HIERARCHY:
		Create a child container from this one. You keep parent container
		as sort of "preset" but you can make changes in the child (so
		you can wire and bind different types and constructors)

		The purpose is to allow using a different implementation for 
		the same interface, and reuse application bindings.
		*/
    Container splitContainer();


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
inline void Container::bindSingleAs(){

    isMultiBase< T, Contracts...>(); //compile time test

    priv::TypeInfoP         types[ sizeof...( Contracts)]
                        { &typeid( Contracts)... };

    priv::SharedUpcastSignature upcasts[ sizeof...( Contracts)]
                        { &priv::shared_upcast< T, Contracts>... };

    container->bindSingleAs( &typeid(T), types, upcasts, sizeof...( Contracts));
}

template< typename T>
inline void Container::bindSingleAsNothing(){
	
	priv::TypeInfoP         types[ 1]
                        { &typeid( T)};

    priv::SharedUpcastSignature upcasts[ 1]
                        { &priv::shared_upcast< T, T> };

    container->bindSingleAs( &typeid(T), types, upcasts, 1);
}

template< typename T, typename A>
inline void Container::bindAs(){

    isMultiBase< T, A>(); //compile time test // TODO: NO!!! allow bind as nothing

    container->bindComponent( &typeid(T), &typeid(A), 
							&priv::upcast< T, A>, sizeof(T));
}

template< typename T>
inline void Container::bindAsNothing(){

    container->bindComponent( &typeid(T), &typeid(T), 
							&priv::upcast< T, T>, sizeof(T));
}


template< typename Impl, typename... SmartPointers>
inline void Container::wire(){

	isWireable< Impl>(); //compile time test

	// -this is to fix a VS bug. Feel free to raise the limit
	static_assert( sizeof...(SmartPointers) <= 6,
		"Unable to wire more than 6 dependencies");

	priv::TypeInfoP types[6]
		{ &typeid(typename SmartPointers::type)... };
						
	container->wire( &typeid(Impl), types, sizeof...( SmartPointers),
					 &factoryFunction< Impl, SmartPointers...>,
					 &instancesFactoryFunction< Impl, SmartPointers...>);
					
	//TODO. make pair (upcast, and new concrete instance togheter) (when compile context)
}

inline Container Container::splitContainer(){
	
	return Container( container->split( container));
}

inline Context Container::createPrototypeContext(){
	
	return Context( container->createContext());
}

} // namespace Infector